#define WIDTH (8)
#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

queue<int> q[WIDTH];
int map[WIDTH][WIDTH];

void check() {
	for (int i = 7; i >= 0; i--) {
		for (int j = 0;j < 8; j++) {
			printf("%d ", map[i][j]);
		} printf("\n");
	}
}

void init(int N, int mTiles[][WIDTH])
{
	// player's board
	for (int i = 0; i < 8; i++) {
		while (!q[i].empty()) q[i].pop();

		for (int j = 0; j < 8; j++) {
			map[i][j] = mTiles[i][j];
		}
	}

	// 예비 타일들은 pop 가능하게 queue로 저장
	for (int i = WIDTH; i < N; i++) {
		for (int j = 0; j < 8; j++) {
			q[j].push(mTiles[i][j]);
		}
	}

	//check();
}

int score(bool isDelete) {
	int score = 0;
	bool mark[8][8] = { false, };
	bool found = false;

	// 1. 가로 검사
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (map[y][x] == 0) continue;
			int num = map[y][x];
			int cnt = 1;
			while (x + cnt < WIDTH && map[y][x + cnt] == num) {
				cnt++;
			}
			if (cnt >= 3) {
				if (cnt == 3) score += 1;
				else if (cnt == 4) score += 4;
				else if (cnt >= 5) score += 9;

				if (isDelete) {
					for (int k = 0; k < cnt; k++) mark[y][x + k] = true;
					found = true;
				}
			}
			x += cnt - 1;
		}
	}

	// 2. 세로 검사
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < WIDTH; y++) {
			if (map[y][x] == 0) continue;
			int num = map[y][x];
			int cnt = 1;
			while (y + cnt < WIDTH && map[y + cnt][x] == num) {
				cnt++;
			}
			if (cnt >= 3) {
				if (cnt == 3) score += 1;
				else if (cnt == 4) score += 4;
				else if (cnt >= 5) score += 9;

				if (isDelete) {
					for (int k = 0; k < cnt; k++) mark[y + k][x] = true;
					found = true;
				}
			}
			y += cnt - 1;
		}
	}

	// 3. 실제 삭제 (0으로 변경)
	if (isDelete && found) {
		for (int y = 0; y < WIDTH; y++) {
			for (int x = 0; x < WIDTH; x++) {
				if (mark[y][x]) map[y][x] = 0;
			}
		}
	}

	return score;
}

int canscore() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			// 오른쪽
			if (j < 7) {
				swap(map[i][j], map[i][j + 1]);
				if (score(false) > 0) {
					swap(map[i][j], map[i][j + 1]);
					return 1;
				}
				swap(map[i][j], map[i][j + 1]);
			}
			// 위쪽
			if (i < 7) {
				swap(map[i][j], map[i + 1][j]);
				if (score(false) > 0) {
					swap(map[i][j], map[i + 1][j]);
					return 1;
				}
				swap(map[i][j], map[i + 1][j]);
			}
		}
	}
	return 0;
}

bool cmp(pair<int, int>& a, pair<int, int>& b) {
	return a.first < b.second;
}

struct target {
	int y;
	int x;
	int dir;
};

target ready() {
	int y=0, x=0;
	vector<int> col;

	// 빈 공간 있으면 채우기
	while (1) {

		for (int i = 0; i < 8; i++) {
			col.clear();
			for (int j = 0; j < 8; j++) {
				if (map[j][i] != 0) {
					col.push_back(map[j][i]);
				}
			}

			for (int j = 0; j < 8; j++) {
				// 기존 맵으로 채우기
				if (j < col.size()) {
					map[j][i] = col[j];
				}
				else {
					// q에서 pop 해와서 밀어넣기
					if (!q[i].empty()) {
						map[j][i] = q[i].front();
						q[i].pop();
					}
					else {
						map[j][i] = 0;
					}
				}
			}
		}

		// 연속되는 3개 이상의 타일 있으면 삭제
		// 다시 빈 공간 채우기
		if (score(true) > 0) {
			continue;
		}

		// 점수 획득 가능한지 확인하기
// 가장 높은 점수 획득 가능한 곳 반환하기

		if (canscore()) {
			break;
		}
		// 없으면 전체 타일 삭제 후 다시 채움
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					map[j][i] = 0;
				}
			}
		}
	}

	int max = -1;
	target t = { -1, -1, -1 };

	// y, x 작은 순서대로 순회하면 2-b, 2-c 조건 자동 만족
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			// 2-d: 오른쪽 먼저 검사
			if (x < 7) {
				if (map[y][x] != map[y][x + 1]) {
					swap(map[y][x], map[y][x + 1]);
					int s = score(false);
					swap(map[y][x], map[y][x + 1]);

					if (s > 0 && s > max) {
						max = s;
						t = { y, x, 0 }; // 0: Right
					}
				}
			}
			// 위쪽 검사
			if (y < 7) {
				if (map[y][x] != map[y + 1][x]) {
					swap(map[y][x], map[y + 1][x]);
					int s = score(false);
					swap(map[y][x], map[y + 1][x]);

					if (s > 0 && s > max) {
						max = s;
						t = { y, x, 1 }; // 1: Up
					}
				}
			}
		}
	}
	return t;
}

int play(int y, int x, int dir) {
	int Score=0;
	int newy, newx;

	// 위치 교환
	if (dir == 0) { // Right
		newy = y;
		newx = x + 1;
	}
	else { // Up
		newy = y + 1;
		newx = x;
	}

	swap(map[y][x], map[newy][newx]);
	Score += score(true);
	// 점수 얻음

	return Score;
}

int after() {
	int Score=0, tmp=0;
	vector<int> col;

	while (1) {
		for (int i = 0; i < 8; i++) {
			col.clear();

			for (int j = 0; j < 8; j++) {
				if (map[j][i] != 0) {
					col.push_back(map[j][i]);
				}
			}

			for (int j = 0; j < 8; j++) {
				// 기존 맵으로 채우기
				if (j < col.size()) {
					map[j][i] = col[j];
				}
				else {
					// q에서 pop 해와서 밀어넣기
					if (!q[i].empty()) {
						map[j][i] = q[i].front();
						q[i].pop();
					}
					else {
						map[j][i] = 0;
					}
				}
			}
		}

		tmp = score(true);
		if (tmp == 0) break;
		Score += tmp;
	}

	return Score;
}

int mRet[5];
int* takeTurn()
{
	int score, nearY=0, nearX=0;

	target t = ready();

	score = play(t.y, t.x, t.dir);

	score += after();

	if (t.dir == 0) { // Right
		nearY = t.y;
		nearX = t.x + 1;
	}
	else { // Up
		nearY = t.y + 1;
		nearX = t.x;

	}

	mRet[0] = score;
	mRet[1] = t.y;
	mRet[2] = t.x;
	mRet[3] = nearY;
	mRet[4] = nearX;

	return mRet;
}