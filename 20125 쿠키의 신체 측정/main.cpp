/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>

using namespace std;

int N; // 한 변의 길이
int map[1005][1005] = { 0 };
char tmp;
int x, y; // 심장의 위치 좌표
int flag = 0;
int length = 0;
int leg_x, leg_y;

int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int test_case;
	int T;

	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	//cin >> T; 
	T=1;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/

	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.

			 쿠키 신체 측정
			 map : 1,1 ~ N,N
			 머리 바로 아랫 칸에 1칸 크기의 심장 위치
			 심장을 기준으로 왼쪽 팔, 오른쪽 팔, 허리, 왼쪽다리, 오른쪽다리 존재
		 */
		 /////////////////////////////////////////////////////////////////////////////////////////////
		
		cin >> N;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				map[i][j] = 0;
			}
		}
		flag = 0;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> tmp;
				if (tmp == '*' && flag == 0) { map[i][j] = 1; x = i; y = j; flag = 1; }
				else if (tmp == '*') {
					map[i][j] = 1;
				}
			}
		}

		/*for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				cout << map[i][j];
			}
			cout << '\n';
		}*/

		// 심장 위치 좌표
		cout << x+1 << ' ' <<  y << '\n';
		
		// 심장 위치 기준 왼쪽 팔
		int i = x+1;
		for (int j = y-1; j >= 1; j--) {
				if (map[i][j] == 1){
					length++;
			}
		}
		cout << length << ' ';
		length = 0;

		// 오른쪽 팔
		for (int j = y+1; j <= N; j++) {
			if (map[i][j] == 1) {
				length++;
			}
		}
		cout << length << ' ';
		length = 0;

		// 허리
		int j = y;
		for (int i = x+2; i <= N; i++) {
			if (map[i][j] == 1) {
				length++;
			}
			else if (map[i][j] == 0) {
				leg_x = i;
				leg_y = j;
				break;
			}
		}
		cout << length << ' ';
		length = 0;

		// 왼쪽 다리
		j = leg_y-1;
		for (int i = leg_x; i <= N; i++) {
			if (map[i][j] == 1) {
				length++;
			}
		}
		cout << length << ' ';
		length = 0;

		// 오른쪽 다리
		j = leg_y + 1;
		for (int i = leg_x; i <= N; i++) {
			if (map[i][j] == 1) {
				length++;
			}
		}
		cout << length << '\n';
		length = 0;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}