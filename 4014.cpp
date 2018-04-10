/*
4014. [모의 SW 역량테스트] 활주로 건설
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeW7FakkUDFAVH
*/

#include <cstdio>

int testcase, result, N, X;
int map[25][25], x, sub_x;
int now, next;
int i, j, k;

int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		scanf("%d %d", &N, &X);
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
			}
		}
		for (i = 0; i <= N; i++) {
			map[i][N] = -1;
			map[N][i] = -1;
		}

		//옆으로 먼저 탐색 
		for (i = 0; i < N; i++) {
			x = X;
			for (j = 0; j < N; j++) {
				now = map[i][j], next = map[i][j + 1];
				if (next == -1) continue;

				if (now == next) x--;
				else if (now + 1 == next) { //높아졌는데
					if (x > 1) break;
					else x = X;
				}
				else if (now - 1 == next) {
					for (k = j + 2; k < N; k++) {
						if (map[i][k] != next) break;
					}
					sub_x = k - j - 1;
					if (sub_x < X) break;
					else {
						j += X - 1;
						x = X + 1;
					}
				}
				else break;
			}
			if (j == N) result++;
		}

		//밑으로 탐색 
		for (j = 0; j < N; j++) {
			x = X;
			for (i = 0; i < N; i++) {
				now = map[i][j], next = map[i + 1][j];
				if (next == -1) continue;

				if (now == next) x--;
				else if (now + 1 == next) { //높아짐?
					if (x > 1) break;
					else x = X;
				}
				else if (now - 1 == next) {
					for (k = i + 2; k < N; k++) {
						if (map[k][j] != next) break;
					}
					sub_x = k - i - 1;
					if (sub_x < X) break;
					else {
						i += X - 1;
						x = 1 + X;
					}
				}
				else break;
			}
			if (i == N) result++;
		}

		printf("#%d %d\n", t, result);
		result = 0;
	}
	return 0;
}