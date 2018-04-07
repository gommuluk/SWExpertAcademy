/*
1953. [모의 SW 역량테스트] 탈주범 검거
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpLlKAQ4DFAUq
*/

#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

class Pos {
public:
	int x;
	int y;

	Pos() {}
	Pos(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
int testcase, result;
int N, M, R, C, L;
int pipe[55][55], level[55][55];
bool visit[55][55];
queue<Pos> q;
Pos p;

void go_there(int x, int y, int px, int py) {
	q.push(Pos(x, y));
	level[x][y] = level[px][py] + 1;
	visit[x][y] = true;
}

void go_up(int x, int y, int px, int py) {
	if (!visit[x][y]) {//방문 안 한 점에 대해
					   //그 점이 '아래로' 뚫려있어야 한다.
		if (pipe[x][y] == 1 || pipe[x][y] == 2 || pipe[x][y] == 5 || pipe[x][y] == 6) {
			go_there(x, y, px, py);
		}
	}
	return;
}
void go_down(int x, int y, int px, int py) {
	if (!visit[x][y]) {
		if (pipe[x][y] == 1 || pipe[x][y] == 2 || pipe[x][y] == 4 || pipe[x][y] == 7) {
			go_there(x, y, px, py);
		}
	}
	return;
}
void go_left(int x, int y, int px, int py) {
	if (!visit[x][y]) {
		if (pipe[x][y] == 1 || pipe[x][y] == 3 || pipe[x][y] == 4 || pipe[x][y] == 5) {
			go_there(x, y, px, py);
		}
	}
	return;
}
void go_right(int x, int y, int px, int py) {
	if (!visit[x][y]) {
		if (pipe[x][y] == 1 || pipe[x][y] == 3 || pipe[x][y] == 6 || pipe[x][y] == 7) {
			go_there(x, y, px, py);
		}
	}
	return;
}

void BFS(void) {

	while (!q.empty()) {
		p = q.front();
		q.pop();

		int now_x = p.x, now_y = p.y;
		if (level[now_x][now_y] > L) {
			visit[now_x][now_y] = false;
			continue;
		}

		switch (pipe[now_x][now_y]) {
		case 1:
			go_up(now_x - 1, now_y, now_x, now_y);
			go_left(now_x, now_y - 1, now_x, now_y);
			go_down(now_x + 1, now_y, now_x, now_y);
			go_right(now_x, now_y + 1, now_x, now_y);

			break;
		case 2:
			go_up(now_x - 1, now_y, now_x, now_y);
			go_down(now_x + 1, now_y, now_x, now_y);

			break;
		case 3:
			go_left(now_x, now_y - 1, now_x, now_y);
			go_right(now_x, now_y + 1, now_x, now_y);

			break;
		case 4:
			go_up(now_x - 1, now_y, now_x, now_y);
			go_right(now_x, now_y + 1, now_x, now_y);

			break;
		case 5:
			go_down(now_x + 1, now_y, now_x, now_y);
			go_right(now_x, now_y + 1, now_x, now_y);

			break;
		case 6:
			go_left(now_x, now_y - 1, now_x, now_y);
			go_down(now_x + 1, now_y, now_x, now_y);

			break;
		case 7:
			go_up(now_x - 1, now_y, now_x, now_y);
			go_left(now_x, now_y - 1, now_x, now_y);

			break;
		}
	}
}

int main() {

	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				scanf("%d", &pipe[i][j]);
			}
		}

		go_there(R, C, R, C);
		BFS();

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (visit[i][j]) {
					result++;
					visit[i][j] = false;
				}
				level[i][j] = 0;
				pipe[i][j] = 0;
			}
		}

		printf("#%d %d\n", t, result);
		result = 0;
	}
	return 0;
}