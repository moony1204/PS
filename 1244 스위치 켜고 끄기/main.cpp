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

int n_switch, n_students;
int switches[105];
int sex, n;

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
	T = 1;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/

	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.

			 1=스위치 켜짐 0 꺼짐
			 남= 스위치 번호가 자기 수의 배수면 상태 바꿈
			 여= 같은 번호 기준 양 옆으로 좌우 대칭인 가장 큰 구간 상태 바꿈

			 입력
			 - 스위치 개수 (100 이하)
			 - 각 스위치 상태
			 - 학생수 (100 이하)
			 - 학생 성별 (1=남 2=여) 학생 받은 수

			 출력
			 - 한 줄에 20개씩 스위치 상태
		 */
		 /////////////////////////////////////////////////////////////////////////////////////////////

		// 스위치 초기 입력
		cin >> n_switch;
		for (int i = 1; i <= n_switch; i++) {
			cin >> switches[i];
		}

		// 학생 정보 입력하며 시뮬레이션
		cin >> n_students;
		for (int i = 0; i < n_students; i++) {
			cin >> sex >> n;

			// 남학생의 경우 n의 배수들 상태 바꿈
			if (sex == 1) {
				// 몇 번 바꿀 건지 전체 스위치수를 n으로 나눠 몫 구함
				int cnt = n_switch / n;
				// for loop 돌며 arr[i] ^ 1로 비트 플립
				for (int j = 1; j <= cnt; j++) {
					int idx = n * j;
					switches[idx] = switches[idx] ^ 1;
				}
			}
			// 여학생의 경우 좌우 대칭 구간 찾아 상태 바꿈
			if (sex == 2) {
				int j = 1;
				switches[n] = switches[n] ^ 1;
				while ((switches[n - j] == switches[n + j]) && (n - j > 0) && (n + j <= n_switch)) {
					switches[n - j] = switches[n - j] ^ 1;
					switches[n + j] = switches[n + j] ^ 1;
					j++;
				}
			}
			/*
			cout << sex << ' ' << n << ' ';
			for (int i = 1; i <= n_switch; i++) {
				cout << switches[i] << ' ';
			} cout << '\n';
			*/
		}

		int cnt = 0;
		for (int i = 1; i <= n_switch; i++) {
			cout << switches[i] << ' ';
			if (++cnt == 20) { cnt = 0; cout << '\n'; }
		}

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}