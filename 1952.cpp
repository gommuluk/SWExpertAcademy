/*
1952. [모의 SW 역량테스트] 수영장
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq
*/

#include <cstdio>
#define day 0
#define mon_1 1
#define mon_3 2
#define year 3
#define INF 987654321

int testcase, cost[4], plan[15], min_cost[15];

int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		for (int i = 0; i < 4; i++) scanf("%d", &cost[i]);
		for (int i = 1; i <= 12; i++) scanf("%d", &plan[i]);

		for (int i = 1; i <= 12; i++) {
			if (plan[i] * cost[day] >= cost[mon_1]) plan[i] = cost[mon_1];
			else plan[i] *= cost[day];
		}
		
		for (int i = 1; i <= 12; i++) {
			min_cost[i] = min_cost[i - 1] + plan[i];
			if (i - 3 >= 0){
				if (min_cost[i] > min_cost[i - 3] + cost[mon_3])  min_cost[i] = min_cost[i - 3] + cost[mon_3];
            }
		}
		if (min_cost[12] > cost[year]) min_cost[12] = cost[year];
		printf("#%d %d\n", t, min_cost[12]);
	}
	return 0;
}