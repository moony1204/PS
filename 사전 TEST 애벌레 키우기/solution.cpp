#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>
#include<map>

using namespace std;

int Map[2005][2005];
int timeG;
int n;
int dx[] = { -1, 0, 1, 0 }; // 시계방향
int dy[] = { 0, 1, 0, -1 };

struct RESULT
{
	int cnt = 0;
	int IDs[5] = { 0, 0, 0, 0, 0 };
};

struct bug {
	int dir;
	int id;
	int length;
	int turn; // 0이면 dir++ 하고 length-2로 세팅
	deque<pair<int, int>> mom;
	int tmpG;
	int dead;
};

/*
void check(){
	cout << timeG << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << Map[i][j] << ' ';
		}cout << '\n';
	}
	cout << '\n';
}*/
vector<bug> buglist;

bool movecmp(const pair<int, pair<int, int>>& a, const pair<int, pair<int, int>>& b) {
	if (a.second.first != b.second.first) {
		return a.second.first < b.second.first;
	}
	return a.second.second < b.second.second;
}

void init(int N)
{
	n = N;
	timeG = 0;
	buglist.clear();

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			Map[i][j] = 0;
		}
	}
}

void move(int diff) {

	for (int t = 0; t < diff; t++) {
		timeG++;

		int B = (int)buglist.size();

		// 성장 여부, 이후 길이
		vector<bool> is_growing(B, false);
		vector<int> len_after_move(B, 0);
		for (int i = 0; i < B; ++i) {
			if (!buglist[i].dead && buglist[i].tmpG > 0) is_growing[i] = true;
			// dead여도 값은 채워두면 편함(어차피 안 씀)
			len_after_move[i] = buglist[i].length + (is_growing[i] ? 1 : 0);
		}

		vector<pair<int, pair<int, int>>> next_moves;
		next_moves.reserve(B);

		// 다음 위치 모으기...
		for (int i = 0; i < B; ++i) {
			if (buglist[i].dead) continue;

			bug& b = buglist[i];

			if (b.turn == 0) {
				b.dir = (b.dir + 1) % 4;
				b.turn = b.length - 1;
			}

			int nx = b.mom.front().first + dx[b.dir];
			int ny = b.mom.front().second + dy[b.dir];
			next_moves.push_back({ i, {nx, ny} });

			// 안 자라면 맵에서 미리 지움
			if (!is_growing[i]) {
				auto tail = b.mom.back();
				if (Map[tail.first][tail.second] == i + 1) {
					Map[tail.first][tail.second] = 0;
				}
			}
		}

		// 충돌.... 이전에 좌표 기반 sort
		sort(next_moves.begin(), next_moves.end(), movecmp);

		vector<pair<int, int>> collisions; // 박는애 박히는 애
		collisions.reserve((int)next_moves.size());

		for (int k = 0; k < (int)next_moves.size(); ) {
			int nx = next_moves[k].second.first;
			int ny = next_moves[k].second.second;

			int j = k + 1;
			while (j < (int)next_moves.size() &&
				next_moves[j].second.first == nx &&
				next_moves[j].second.second == ny) {
				j++;
			}

			bool is_out = (nx < 0 || nx >= n || ny < 0 || ny >= n);

			// 이동 후 칸의 종류
			int body_victim = -1;
			if (!is_out && Map[nx][ny] != 0) {
				int idx = Map[nx][ny] - 1;
				auto tail = buglist[idx].mom.back();
				if (!(tail.first == nx && tail.second == ny && !is_growing[idx])) {
					body_victim = idx;
				}
			}

			// 그룹에 속한 이동자 처리
			for (int idx = k; idx < j; ++idx) {
				int curr = next_moves[idx].first;

				// 같은 칸으로 2개 이상 머리 진입 => head-head로 전부 사망
				// or out => 사망
				// or body 충돌 => 사망
				if ((j - k > 1) || is_out || (body_victim != -1)) {
					buglist[curr].dead = true;
				}

				// 몸 충돌이면 박는애 박힌애 기록
				// 잠재력은 나중에 .....
				if (!is_out && body_victim != -1) {
					collisions.push_back({ curr, body_victim });
				}
			}

			k = j;
		}

		// 잠재력
		// 박힌애가 살아잇어야되고 박는애는 성장 후 길이 반영
		for (auto& col : collisions) {
			int attacker = col.first;
			int victim = col.second;

			if (!buglist[victim].dead) {
				buglist[victim].tmpG += len_after_move[attacker];
			}
		}

		// 죽은 벌레 제거 / 산 벌레는 머리 추가 + (성장면 length++, tmpG--)
		for (int k = 0; k < (int)next_moves.size(); ++k) {
			int i = next_moves[k].first;

			if (buglist[i].dead) {
				// 죽는 벌레는 이번 턴 끝에 동시에 소멸
				// 남아있던 몸통도 맵에서 제거
				for (auto& pos : buglist[i].mom) {
					if (Map[pos.first][pos.second] == i + 1) {
						Map[pos.first][pos.second] = 0;
					}
				}
				buglist[i].mom.clear();
			}
			else {
				int nx = next_moves[k].second.first;
				int ny = next_moves[k].second.second;

				buglist[i].mom.push_front({ nx, ny });
				Map[nx][ny] = i + 1;

				buglist[i].turn--;

				if (is_growing[i]) {
					buglist[i].length++;
					buglist[i].tmpG--;
					buglist[i].turn++;
				}
				else {
					buglist[i].mom.pop_back();
				}
			}
		}
	}
}


void join(int mTime, int mID, int mX, int mY, int mLength)
{
	// 최대 400마리
	int diff = mTime - timeG;
	move(diff);

	bug tmp;
	tmp.dir = 0;
	tmp.id = mID;
	tmp.length = mLength;
	tmp.tmpG = 0;
	tmp.dead = 0;
	tmp.turn = 0;
	for (int i = 0; i < mLength; i++) {
		tmp.mom.push_back({ mY + i, mX });
		Map[mY + i][mX] = buglist.size() + 1;
	}
	buglist.push_back(tmp);
}

bool cmp(const int& a, const int& b) {
	// 가장 긴
	if (buglist[a].mom.size() != buglist[b].mom.size()) {
		return buglist[a].mom.size() > buglist[b].mom.size();
	}
	// id 큰
	return buglist[a].id > buglist[b].id;
}

RESULT top5(int mTime)
{
	// 최대 300번 search
	RESULT ret = RESULT();

	int diff = mTime - timeG;
	move(diff);

	vector<pair<int, int>> living;

	vector<int> list;

	for (int i = 0; i < buglist.size(); i++) {
		if (!buglist[i].dead) {
			// 살아있는 벌레들 수집
			list.push_back(i);
			//cout << i << ' ';
		}
	} //cout << '\n';

	// 살아있는 벌레가 5개 이하
	if (list.size() <= 5) {
		ret.cnt = list.size();
		sort(list.begin(), list.end(), cmp);
		for (int i = 0; i < ret.cnt; i++) {
			ret.IDs[i] = buglist[list[i]].id;
		}
	}

	else { // 상위 5개만 골라야함
		ret.cnt = 5;
		sort(list.begin(), list.end(), cmp);
		for (int i = 0; i < 5; i++) {
			ret.IDs[i] = buglist[list[i]].id;
		}
	}

	/*
	cout << mTime << ret.cnt << ' ';
	for (int i = 0; i < ret.cnt; i++) {
		cout << ret.IDs[i] << ' ';
	} cout << '\n';
	*/

	return ret; // dummy
}