

/*
void move(int diff) {
	for (int t = 0; t < diff; t++) {
		vector<bool> willdie(buglist.size(), false);

		for (int i = 0; i < buglist.size(); i++) {
			bug& b = buglist[i];
			if (b.dead) continue; // already dead

			// 방향 체크
			if (b.turn == 0) {
				b.dir = (b.dir + 1) % 4;
				b.turn = b.length - 1;
			}

			// 다음 머리 위치
			int nx = b.mom.front().second + dx[b.dir];
			int ny = b.mom.front().first + dy[b.dir];

			// 위치 이탈로 삭제면 바로 지움
			if (ny < 0 || nx < 0 || ny >= n || nx >= n) {
				for (auto& pos : b.mom) {
					Map[pos.first][pos.second] = 0;
				}
				b.mom.clear();
				b.dead = 1;
			}

			// 성장 가능성
			if (b.tmpG > 0) {
				// 꼬리 안지워도 됨. 길이 늘어남
				b.tmpG--;
				b.turn++;
				b.length++;
			}
			else { // 꼬리 지우기 길이 그대로
				pair<int, int> tail = b.mom.back();
				Map[tail.first][tail.second] = 0;
			}

			int idx = Map[ny][nx];
			if (idx != 0) {
				// 빈 공간이 아님
				bug &tb = buglist[idx - 1];
				int tx = tb.mom.front().second;
				int ty = tb.mom.front().first;

				// 머리인지 확인
				if (ny == ty && nx == tx) {
					// 둘 다 소멸
					willdie[b.id - 1] = true;
					willdie[tb.id - 1] = true;
				}

				// 꼬리 칸인지 확인
				auto tail = tb.mom.back();

				// 꼬리가 빠질 예정이면 충돌 아님
				if (tail.first == ny && tail.second == nx && tb.tmpG == 0) {
					// ㄱㅊㄱㅊ
				}

				else {
					// 부딫힌 b만 소멸
					willdie[b.id - 1] = true;
				}
			}
			Map[ny][nx] = b.id;
			b.turn--;

		}
	}
}*/