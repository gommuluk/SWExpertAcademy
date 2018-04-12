/*
2115. [모의 SW 역량테스트] 벌꿀채취
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V4A46AdIDFAWu
*/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Pos {
public:
	int x;
	int y;
	int profit;

	Pos() {}
	Pos(int x, int y, int p) {
		this->x = x;
		this->y = y;
		profit = p;
	}
};

int testcase, result, N, M, C; 
int map[15][15];
int smaller_than_c, k, end_y;
int map_profit, sub_profit, max_sub_profit;
vector<Pos> vec;

void DFS(int x, int y, int prev_c) {
	int tmp_c = prev_c;

	for (int i = 0; i < M; i++) {
		if (y + i >= end_y) return;
		if (map[x][y + i] <= tmp_c) {
			sub_profit += map[x][y + i] * map[x][y + i];
			tmp_c -= map[x][y + i];
			for (int j = 1; j <= M; j++) {
				DFS(x, y + i + j, tmp_c);
			}
			if (max_sub_profit < sub_profit) max_sub_profit = sub_profit;
			sub_profit -= map[x][y + i] * map[x][y + i];
			tmp_c += map[x][y + i];
		} 
		else return;
	}
}

bool cmp(const Pos &a, const Pos &b) {
	return a.profit > b.profit;
}

int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		scanf("%d %d %d", &N, &M, &C);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &map[i][j]);
			}
		}
	
		for (int i = 1; i <= N; i++) { // 각 가로줄에 대해 
			for (int j = 1; j <= N; j++) {
				
				for (k = 0; k < M; k++) {
					if (j + k > N) break;
					smaller_than_c += map[i][j + k];
					map_profit += map[i][j + k] * map[i][j + k];
				}
				if (smaller_than_c > C) {
					end_y = j + M;
					DFS(i, j, C);
					map_profit = max_sub_profit;
				}
				vec.push_back(Pos(i, j, map_profit));
				map_profit = 0;
				smaller_than_c = 0;
				sub_profit = 0;
				max_sub_profit = 0;
			}
		}

		sort(vec.begin(), vec.end(), cmp);
		
		for (int i = 1; i < vec.size(); i++) {
			if (vec[0].x == vec[i].x && abs(vec[0].y - vec[i].y) < M) continue;
			else {
				result = vec[0].profit + vec[i].profit;
				break;
			}
		}

		printf("#%d %d\n", t, result);
		result = 0;
		vec.clear();	
		for (int i = 0; i < 15; i++) for (int j = 0; j < 15; j++) map[i][j] = 0;
	}
	return 0;
}



