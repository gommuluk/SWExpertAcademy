/*
4008. [모의 SW 역량테스트] 숫자 만들기
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeRZV6kBUDFAVH
*/

#include <cstdio>

int testcase, result;
int N, op[5], num[15];
int RES_MAX = -100000001, RES_MIN = 100000001;
int dfs_result;

void DFS(int pos) {
	if (pos >= N) {
		if (RES_MAX < dfs_result) RES_MAX = dfs_result;
		if (RES_MIN > dfs_result) RES_MIN = dfs_result;
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (op[i] > 0) {
			op[i]--;
			int tmp = dfs_result;

			if (i == 0) dfs_result += num[pos];
			else if (i == 1) dfs_result -= num[pos];
			else if (i == 2) dfs_result *= num[pos];
			else if (i == 3) {
				if (num[pos]) dfs_result /= num[pos];
				else {
					op[i]++;
					continue;
				}
			}

			pos++;
			DFS(pos);
			pos--;
			dfs_result = tmp;
			op[i]++;
		}
	}
}

int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {

		scanf("%d", &N);
		for (int i = 0; i < 4; i++) {
			scanf("%d", &op[i]);
		}
		for (int i = 0; i < N; i++) {
			scanf("%d", &num[i]);
		}
		
		dfs_result = num[0];
		DFS(1);

		result = RES_MAX - RES_MIN;
		printf("#%d %d\n", t, result);
		RES_MAX = -100000001, RES_MIN = 100000001;
	}
	return 0;
}