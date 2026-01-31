#include<iostream>
#include<vector>
#include<deque>

using namespace std;

vector<vector<int>> cnt; // 각 줄별로 알파벳 개수 카운트
int height, width; // 메모장 사이즈
int cursorH, cursorW; // 커서 위치 (0, 0) ~ (h-1, w-1)
vector<deque<char>> memo; // H줄의 벡터 메모장? 각 줄은 deque로 빠른 편집.. 

/*
tc 25개 3초

높이 H, 너비 W의 메모장 (한 줄에 문자 W개 까지만 가능)
초기 저장된 mStr 문자열
커서는 idx 0에 있음
*/

void init(int H, int W, char mStr[])
{
	height = H; width = W; // 메모장 사이즈
	cursorH = 0; cursorW = 0; // 커서 초기 위치 (0,0)
	cnt.clear();
	cnt.assign(H, vector<int>(26, 0)); // 각 줄 별 알파벳 수 초기 세팅 0
	memo.clear();
	memo.assign(H, deque<char>(W, 0)); // 메모장?
}

/* 커서 위치에 문자 mChar 삽입 
삽입 이후 커서 위치는 +1 
삽입한 줄 부터 이후까지 width 넘지 않는지 확인 필요 
3만번 이하 호출 */
void insert(char mChar)
{

}

/* 커서 위치를 mRow-1 mCol-1로 변경 
비어있는 경우 젤 마지막으로 이동, $ 반환
아닐 경우 커서 다음 문자 반환 
3만번 이하 호출 */
char moveCursor(int mRow, int mCol)
{
	return '$';
}

/* 커서 이후의 특정 문자 개수 확인 */
/* cnt[26] arr? 
4만번 이하 호출 */
int countCharacter(char mChar)
{
	return -1;
}
