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

// set 사용 구현 -> timeout. bitmasking 사용해야 함!
/*
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<set>

using namespace std;

string s;
set<int> S;

set<int> allS = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };

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
	* /
	//freopen("input.txt", "r", stdin);
	cin >> T; // T=M
	cin.ignore();
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	* /

	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.

			 add x : 중복 허용 안함. 집합에 자연수 x 추가
			 remove x : 집합에서 x 지움
			 check x : 있으면 1, 없으면 0
			 toggle x : 있으면 지우기, 없으면 추가
			 all : 1~20 다 추가
			 empty : 공집합으로 바꿈
		 * /
		 /////////////////////////////////////////////////////////////////////////////////////////////

		getline(cin, s);
		stringstream ss(s);

		string word;

		vector<string> words;

		while (ss >> word) {
			words.push_back(word);
		}

		
		if (words.front() == "empty") {
			S.clear();
		}
		else if (words.front() == "all") {
			S = allS;
		}
		else {
			int x = stoi(words.back());

			if (words.front() == "add") {
				S.insert(x);
				// no output
			}
			else if (words.front() == "remove") {
				if (S.find(x) != S.end()) { // 있음
					S.erase(x);
				} // 없으면 무시
			}
			else if (words.front() == "check") {
				if (S.find(x) != S.end()) { // 있음
					cout << "1\n";
				}
				else {
					cout << "0\n";
				}
			}
			else if (words.front() == "toggle") {
				if (S.find(x) != S.end()) { // 있음
					S.erase(x);
				}
				else {
					S.insert(x);
				}
			}

		}
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
} */

// bitmasking

#include<iostream>
#include<string>

using namespace std;

string s;
int x;
int bitmask = 0;

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
	cin >> T; // T=M
	cin.ignore();
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/

	for (test_case = 1; test_case <= T; ++test_case)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.

			 add x : 중복 허용 안함. 집합에 자연수 x 추가
			 remove x : 집합에서 x 지움
			 check x : 있으면 1, 없으면 0
			 toggle x : 있으면 지우기, 없으면 추가
			 all : 1~20 다 추가
			 empty : 공집합으로 바꿈
		 */
		 /////////////////////////////////////////////////////////////////////////////////////////////

		cin >> s;
		if (s == "add") {
			cin >> x;
			bitmask = bitmask | (1 << (x - 1));
			// or 연산
		}
		else if (s == "remove") {
			cin >> x;
			bitmask = bitmask & ~(1 << (x - 1));
			// ~ x와 and 함으로써 지움
		}
		else if (s == "check") {
			cin >> x;
			if (bitmask & (1 << (x - 1))) {
				cout << "1\n";
			}
			else {
				cout << "0\n";
			}
		}
		else if (s == "toggle") {
			cin >> x;
			/*if (bitmask & (1 << (x - 1))) {
				bitmask = bitmask & ~(1 << (x - 1));
			}
			else {
				bitmask = bitmask | (1 << (x - 1));
			}*/
			bitmask = bitmask ^ (1 << (x - 1));
			// xor operation!!
		}
		else if (s == "all") {
			bitmask = (1 << 20) -1;
			// 그냥 1 하면 00000011 00001000
		}
		else if (s == "empty") {
			bitmask = 0;
		}
	}
	return 0;
}