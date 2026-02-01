#include<iostream>
#include<vector>
#include<deque>
#include<cstring>
#include<algorithm>

using namespace std;

vector<vector<int>> cnt; // 각 줄별로 알파벳 개수 카운트
int height, width; // 메모장 사이즈
int cursorH, cursorW; // 커서 위치 (0, 0) ~ (h-1, w)
vector<deque<char>> memo; // H줄의 벡터 메모장? 각 줄은 deque로 빠른 편집.. 
int idx;

/*
tc 25개 3초

높이 H, 너비 W의 메모장 (한 줄에 문자 W개 까지만 가능)
초기 저장된 mStr 문자열
커서는 idx 0에 있음
*/

/*
void check() {
	for (int i = 0; i < height; i++) {
		if (memo[i].empty()) break;
		for (int j = 0; j < memo[i].size(); j++) {
			if (cursorH == i && cursorW == j) { printf("|"); }
			printf("%c", memo[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
*/
void init(int H, int W, char mStr[])
{
	height = H; width = W; // 메모장 사이즈
	cursorH = 0; cursorW = 0; // 커서 초기 위치 (0,0)
	cnt.clear();
	cnt.assign(H, vector<int>(26, 0)); // 각 줄 별 알파벳 수 초기 세팅 0
	memo.clear();
	memo.assign(H, deque<char>()); // 메모장?

	int totalLen = strlen(mStr);
	idx = 0;

	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (idx >= totalLen) break; // 문자열 끝에 도달하면 중단

			memo[i].push_back(mStr[idx]); // 메모장에 저장
			cnt[i][mStr[idx] - 'a']++; // 그 줄의 카운트 세기
			idx++;
		}
		if (idx >= totalLen) break;
	}
	//check();
}

/* 커서 위치에 문자 mChar 삽입 
삽입 이후 커서 위치는 +1 
삽입한 줄 부터 이후까지 width 넘지 않는지 확인 필요 
3만번 이하 호출 */
void insert(char mChar)
{
	// 커서 위치에 문자 삽입
	memo[cursorH].insert(memo[cursorH].begin() + cursorW, mChar);
	cnt[cursorH][mChar - 'a']++; // 삽입한 줄에 cnt도 늘림
	idx++;

	if (memo[cursorH].size() > width) { // overflow!
		for (int i = cursorH; i < height - 1; i++) {
			char tmp = memo[i].back(); // 맨 뒤 문자
			memo[i].pop_back(); // 지우고
			cnt[i][tmp - 'a']--; // 카운트 줄이고
			memo[i + 1].push_front(tmp); // 다음줄 앞에 추가
			cnt[i+1][tmp - 'a']++; // 다음줄 카운트 늘림
			if (memo[i+1].size() <= width) { // 다음 줄은 안넘침
				break; // 끝
			}
		}
	}
	cursorW++; // 새로 추가한 문자의 오른쪽에 위치
	if (cursorW == width && cursorH + 1 < height) {
		cursorH++; // 다음줄
		cursorW = 0;
	}
	//printf("insert %c\n", mChar);
	//check();
}

/* 커서 위치를 mRow-1 mCol-1로 변경 
비어있는 경우 젤 마지막으로 이동, $ 반환
아닐 경우 커서 다음 문자 반환 
3만번 이하 호출 */
char moveCursor(int mRow, int mCol)
{
	//char ans;
	int r = mRow - 1; int c = mCol - 1;
	/*while (memo[mRow].empty()) {
		//cursorH = ;
		//cursorW = ;
		mRow--;
	} if (mRow < 0) { mRow = 0; }
	cursorH = mRow;
	cursorW = min((int)memo[mRow].size()-1, mCol-1);*/
	if (r*width + mCol > idx) {
		cursorH = idx / width;
		cursorW = idx % width;

		if (cursorH >= height) {
			cursorH = height - 1; cursorW = width;
		}
		//printf("cursor $\n");
		//check();
		return '$';
	}
	else {
		cursorH = r;
		cursorW = c;
	}
	//printf("cursor %c\n", memo[cursorH][cursorW]);
	//check();
	return memo[cursorH][cursorW];
}

/* 커서 이후의 특정 문자 개수 확인 */
/* cnt[26] arr? 
4만번 이하 호출 */
int countCharacter(char mChar)
{
	int ans = 0;
	int target = mChar - 'a';

	for (int i = cursorH; i < height; i++) {
		ans += cnt[i][target];
	}

	for (int j = 0; j < cursorW; j++) {
		if (memo[cursorH][j] == mChar) {
			ans--;
		}
	}

	//printf("count %d\n\n", ans);

	return ans;
}
