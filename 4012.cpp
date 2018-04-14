/*
4012. [모의 SW 역량테스트] 요리사
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeUtVakTMDFAVH
*/

#include <cstdio>
#include <cmath>
#define forA 1
#define forB 2
using namespace std;

int testcase, min_value = (1 << 30);
int N, map[20][20];
int for_whom[20];
int divided_N;

void calc() {
	int food_a[10] = { 0, }, food_b[10] = { 0, };
	int count_a = 0, count_b = 0;
	int cal_a = 0, cal_b = 0;

	for (int i = 1; i <= N; i++) {
		if (for_whom[i] == forA) food_a[++count_a] = i;
		else if (for_whom[i] == forB) food_b[++count_b] = i;
	}
	if (count_a != divided_N || count_b != divided_N) return;

	int x, y;
	for (int i = 1; i < divided_N; i++) {
		for (int j = i + 1; j <= divided_N; j++) {
			x = food_a[i], y = food_a[j];
			cal_a += map[x][y] + map[y][x];
		}
	}
	for (int i = 1; i < divided_N; i++) {
		for (int j = i + 1; j <= divided_N; j++) {
			x = food_b[i], y = food_b[j];
			cal_b += map[x][y] + map[y][x];
		}
	}

	int tmp = abs(cal_a - cal_b);
	if (min_value > tmp) min_value = tmp;
}

void DFS(int num, int count_a, int count_b) {
	if (num > N) {
		calc();
		return;
	}
	if (count_a > 0) {
		for_whom[num] = forA;
		DFS(num + 1, count_a - 1, count_b);
	}
	if (count_b > 0) {
		for_whom[num] = forB;
		DFS(num + 1, count_a, count_b - 1);
	}
}

int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		divided_N = N / 2;
		DFS(1, divided_N, divided_N); 

		printf("#%d %d\n", t, min_value);
		min_value = (1 << 30);
	}
	return 0;
}