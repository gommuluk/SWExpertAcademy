/*
2382. [모의 SW 역량테스트] 미생물 격리
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV597vbqAH0DFAVl
*/

#include <cstdio>
#include <cstring>

#define up 1
#define down 2
#define left 3
#define right 4

class Pos {
public:
	int x;
	int y;
	int num;
	int dir;

	Pos() {}
	Pos(int x, int y, int num, int dir) {
		this->x = x;
		this->y = y;
		this->num = num;
		this->dir = dir;
	}
};

int testcase, result;
int map[111][111][5], mistake[111][111][5];
int N, T, K; 
int x, y, n, p;

int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		scanf("%d %d %d", &N, &T, &K);
		for (int i = 0; i < K; i++) {
			scanf("%d %d %d %d", &x, &y, &n, &p);
			map[x][y][p] = n;
		}
		
		while (T--) {
			for (int i = 1; i < N - 1; i++) { // 약 뿌려진 모서리 처리
				if (map[1][i][up]) { // 위쪽 모서리 처리
					mistake[0][i][down] = map[1][i][up] / 2;
					map[1][i][up] = 0;
				}
				if (map[i][1][left]) { // 왼쪽 모서리 처리
					mistake[i][0][right] = map[i][1][left] / 2;
					map[i][1][left] = 0;
				}
				if (map[N - 2][i][down]) { // 아래쪽 모서리 처리
					mistake[N - 1][i][up] = map[N - 2][i][down] / 2;
					map[N - 2][i][down] = 0;
				}
				if (map[i][N - 2][right]) { // 오른쪽 모서리 처리
					mistake[i][N - 1][left] = map[i][N - 2][right] / 2;
					map[i][N - 2][right] = 0;
				}
			}

			for (int i = 1; i < N - 1; i++) { // 가운데부분 처리
				for (int j = 1; j < N - 1; j++) {
					int sum = 0, dir_num = 0, dir = 0;

					if ((i - 1) >= 0 && map[i - 1][j][down]) { // 위에서 내려올 게 있니?
						sum += map[i - 1][j][down]; // 있으면 수를 더하자
						if (dir_num < map[i - 1][j][down]) { // 방향 결정할 건데, 네가 대장이니?
							dir_num = map[i - 1][j][down]; // 그렇다면 네 수를 기억할게
							dir = down; // 방향 너 가져
						}
						map[i - 1][j][down] = 0; // 네 기록은 지울게
					}
					if ((j - 1) >= 0 && map[i][j - 1][right]) { // 왼쪽에서 넘어올 게 있니?
						sum += map[i][j - 1][right];
						if (dir_num < map[i][j - 1][right]) {
							dir_num = map[i][j - 1][right];
							dir = right;
						}
						map[i][j - 1][right] = 0;
					}
					if ((i + 1) < N && map[i + 1][j][up]) { // 아래에서 올라오니?
						sum += map[i + 1][j][up];
						if (dir_num < map[i + 1][j][up]) {
							dir_num = map[i + 1][j][up];
							dir = up;
						}
						map[i + 1][j][up] = 0;
					}
					if ((j + 1) < N && map[i][j + 1][left]) { // 오른쪽에서 오니?
						sum += map[i][j + 1][left];
						if (dir_num < map[i][j + 1][left]) {
							dir_num = map[i][j + 1][left];
							dir = left;
						}
						map[i][j + 1][left] = 0;
					}
					
					mistake[i][j][dir] = sum; // 정리 다 됐으니 정보 입력할게~
				}
			}


			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					for (int k = 1; k <= 4; k++) {
						map[i][j][k] = mistake[i][j][k];
						mistake[i][j][k] = 0;
					}
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 1; k <= 4; k++) {
					result += map[i][j][k];
				}

				memset(map[i][j], 0, sizeof(int) * 5);
				memset(mistake[i][j], 0, sizeof(int) * 5);
			}
		}

		printf("#%d %d\n", t, result);
		result = 0;
	}
	return 0;
}