#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>

using namespace std;

struct RESULT_E
{
	int success;
	char locname[5];
};

struct RESULT_S
{
	int cnt;
	char carlist[5][8];
};

struct CAR {
	int startime;
	int tow;
	int area;
	int slot;

	int parked; // 0:나감, 1:주차, 2:견인
	int x;
	char y;
	int z;

	char carNo[10];
};

map<string, CAR> cars;
int slot_left[26];
set<int> slots[26];

// for search
vector<CAR*> carIndex[10000];

// for upddate
priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> tow_scheduler;

int leftTime;
int num, mslot;

void init(int N, int M, int L)
{
	// N 개의 구역
	fill(slot_left, slot_left + 26, 0);
	fill(slot_left, slot_left + N, M);
	num = N;
	mslot = M;

	// M 개의 슬롯
	for (int i = 0; i < N; i++) {
		slots[i].clear();
		for (int j = 0; j < M; j++) {
			slots[i].insert(j);
		}
	}

	// 차 초기화
	cars.clear();
	for (int i = 0; i < 10000; i++) carIndex[i].clear();
	while (!tow_scheduler.empty()) tow_scheduler.pop();

	// 최대 주차 가능 시간 L
	leftTime = L;

	return;
}

void update(int mTime) {
	while (!tow_scheduler.empty()) {
		pair<int, string> cur = tow_scheduler.top();

		if (cur.first > mTime) break;
		// 젤 빠른 스케줄이 지금보다 나중임
		// 지금 견인할 차 없음


		// 여기서부턴 견인
		tow_scheduler.pop();

		auto it = cars.find(cur.second);
		if (it == cars.end()) continue; //없

		CAR& car = it->second;

		// 주차 되어잇고 지금이 time일때만.. 
		if (car.parked == 1 && car.tow == cur.first) {
			car.parked = 2;

			slot_left[car.area]++;
			slots[car.area].insert(car.slot);
		}
	}
}

RESULT_E enter(int mTime, char mCarNo[])
{
	update(mTime);

	RESULT_E res_e;

	res_e.success = -1;

	int max = 0;
	int idx = -1;

	// 구역 선정
	for (int i = 0; i < num; i++) {
		if (slot_left[i] > max) {
			max = slot_left[i];
			idx = i;
		}
	}

	// 슬롯 없으면 주차 실패
	if (idx == -1) {
		res_e.success = 0;
		res_e.locname[0] = '\0';

		auto it = cars.find(mCarNo);
		if (it != cars.end()) {
			if (it->second.parked == 2) {
				// 성공 여부 상관 없이 견인이면 기록 삭제!!
				it->second.parked = 0;
			}
		}

		return res_e;
	}

	// 빈 슬롯 수 -> 알파벳 순 - > max 조건으로 자동 성립
	// 슬롯 선정
	// 숫자 작은 순서
	int slot = *slots[idx].begin();
	slots[idx].erase(slots[idx].begin());
	// 구역 내 빈자리 줄임
	slot_left[idx]--;
	
	res_e.success = 1; // 일단 성공하긴 함
	sprintf(res_e.locname, "%c%03d", 'A' + idx, slot);

	// 차 정보 삽입
	CAR tmp;
	tmp.startime = mTime;
	tmp.tow = mTime + leftTime;
	tmp.area = idx;
	tmp.slot = slot;
	tmp.parked = 1;

	strcpy(tmp.carNo, mCarNo);
	sscanf(mCarNo, "%d%c%d", &tmp.x, &tmp.y, &tmp.z);

	if (cars.find(mCarNo) == cars.end()) {
		cars[mCarNo] = tmp;
		carIndex[tmp.z].push_back(&cars[mCarNo]);
	}
	else {
		// 이미 있는 거면 덮어씀
		cars[mCarNo] = tmp;
	}

	// 견인 스케줄도 넣어둠
	tow_scheduler.push({ tmp.tow, mCarNo });

	return res_e;
}

int pullout(int mTime, char mCarNo[])
{
	update(mTime);

	// 주차 X, 견인 X
	if (cars.find(mCarNo) == cars.end()) {
		return -1;
	}

	if (cars[mCarNo].parked == 0) {
		return -1;
	}

	if (cars[mCarNo].parked == 1) {
		slot_left[cars[mCarNo].area]++;
		slots[cars[mCarNo].area].insert(cars[mCarNo].slot);

		// 슬롯은 빔
		cars[mCarNo].parked = 0;
		return mTime - cars[mCarNo].startime;
	}

	if (cars[mCarNo].parked == 2) {
		// (주차된 기간 + 견인된 기간 * 5) * (-1)
		// 슬롯은 빔
		cars[mCarNo].parked = 0;
		int ans = -1 * (leftTime + (mTime - cars[mCarNo].tow) * 5);
		return  ans;
	}

	return -1;
}

bool cmp(const CAR* a, const CAR* b) {
	if (a->parked != b->parked) {
		return a->parked < b->parked;
	}
	if (a->x != b->x) {
		return a->x < b->x;
	}
	return a->y < b->y;
}

RESULT_S search(int mTime, char mStr[])
{
	update(mTime);

	RESULT_S res_s;
	vector<CAR*> searchList;

	res_s.cnt = 0;

	int Z = 0;
	sscanf(mStr, "%d", &Z);

	// z인 애들 중에서만 주차 여부로 넣음
	for (CAR* car : carIndex[Z]) {
		if (car->parked != 0) {
			searchList.push_back(car);
		}
	}

	// 정렬
	sort(searchList.begin(), searchList.end(), cmp);

	int count = 0;
	for (CAR* c : searchList) {
		if (count >= 5) break; // 최대 5개만 !!
		strcpy(res_s.carlist[count], c->carNo);
		count++;
	}
	res_s.cnt = count;

	return res_s;
}