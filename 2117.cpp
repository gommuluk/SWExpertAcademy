/*
2117. [모의 SW 역량테스트] 홈 방범 서비스
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V61LqAf8DFAWu
*/

#include <cstdio>
#include <cmath>
using namespace std;

int testcase, N, M;
int map[25][25];
int cost[25]; // 각 K가 가진 비용
int max_house, max_cost, service_house, max_service_house;
int K; // 처음 설정된 방범서비스 크기
int tmp_i;

int main() {
	scanf("%d", &testcase);

	// 회사 측에서 지불할 비용을 먼저 계산한다. 
	for (int k = 1; k <= 22; k++) { // 입력으로 들어올 수 있는 N의 최대값이 20이므로 K의 최대값은 22이 된다.
		cost[k] = k * k + (k - 1)*(k - 1);
	}
	
	for (int t = 1; t <= testcase; t++) {
		scanf("%d %d", &N, &M);
		for (int i = 1; i <= N; i++) { // 지도 입력 받음
			for (int j = 1; j <= N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j]) max_house++;
			}
		}

		max_cost = max_house * M; // (전체 비용) * (전체 집 수) = 마을에서 낼 수 있는 최대 비용
		for (int k = 1; k <= 22; k++) { // 최대 비용보다는 작은 범위를 서비스 할 수 있으므로 해당하는 K를 찾는다
			K = k - 1;
			if (cost[k] > max_cost) break;
		}

		while (K > 0) { // 가장 큰 K부터 K가 1이 될 때까지 탐색			
			for (int a = 1; a <= N; a++) { // a와 b는 서비스 지역의 중심 좌표이다.
				for (int b = 1; b <= N; b++) { // 중심 좌표를 (0,0)에서 (N,N)까지 탐색할 예정

					for (int j = (-1)*(K - 1); j <= (K - 1); j++) { // 각 중심점에서 서비스 지역 탐색..
						tmp_i = (K - 1) - abs(j);
						for (int i = (-1)*tmp_i; i <= tmp_i; i++) {
							if (a + i < 1 || a + i > N || b + j < 1 || b + j > N) continue;
							if (map[a + i][b + j] == 1) service_house++;
						}
					}

					if (service_house*M >= cost[K] && max_service_house < service_house) max_service_house = service_house;
					service_house = 0;
				}
			}

			if (max_service_house) break;
			else K--; // 서비스 지역을 줄인다
		}

		//손해를 보지 않으면서 홈방범 서비스를 가장 많은 집들에 제공하는 서비스 영역을 찾았을 때, 그 때의 서비스를 제공 받는 집들의 수
		printf("#%d %d\n", t, max_service_house);
		max_house = 0; service_house = 0, max_service_house = 0;
	}
	return 0;
}
