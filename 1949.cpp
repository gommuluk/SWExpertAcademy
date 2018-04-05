/*
1949.[PROBLEM] [모의 SW 역량테스트] 등산로 조성
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq
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

int testcase, N, K, max_result, max_high;
int matrix[10][10]; //map
queue<Pos> q; //봉우리 좌표 저장
Pos p;
bool visit[10][10]; // DFS 방문 여부
int x_move[4] = { -1,0,1,0 }, y_move[4] = { 0,-1,0,1 };
bool K_flag = false; //깎음 여부
int result; //그래프 깊이

void DFS(int x, int y) {

	visit[x][y] = true;
	result++; 

	for (int i = 0; i < 4; i++) {
		int x_next = x + x_move[i], y_next = y + y_move[i]; //다음 좌표 찾기
		if (x_next < 1 || x_next > N || y_next < 1 || y_next > N) continue; 

		if (!visit[x_next][y_next]) { //방문하지 않은 점에 대해 
			if (K_flag) { //깎은 곳이 있다면
				if (matrix[x_next][y_next] < matrix[x][y]) // 더이상 깎을 수 없으므로 기본 조건만 체크
					DFS(x_next, y_next);
			}
			else { //깎은 곳이 없다면 더 깎을 수 있어
				if (matrix[x_next][y_next] < matrix[x][y]) 
					DFS(x_next, y_next);
				else { 
					for (int k = 1; k <= K; k++) { //가장 얕게 깎기 시작합니다.. 최대한 높아야 좋지 않을까요
						if (matrix[x_next][y_next] - k < matrix[x][y]) {
							matrix[x_next][y_next] -= k;
							K_flag = true; //깎음
							DFS(x_next, y_next);
							matrix[x_next][y_next] += k;//원위치
							K_flag = false;
						}						
					}
				}
			}			
		} 
	} 
	
	if (max_result < result) max_result = result; //최대값 저장
	result--;
	visit[x][y] = false;
}

int main() {

	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {

		//입력
		scanf("%d %d", &N, &K);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &matrix[i][j]);
				if (max_high < matrix[i][j]) max_high = matrix[i][j];
			}
		}

		//최고 봉우리 찾기
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (matrix[i][j] == max_high)
					q.push(Pos(i, j));
			}
		}

		while (!q.empty()) {
			p = q.front();
			q.pop();

			DFS(p.x, p.y);
			result = 0;
			K_flag = false;
			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					visit[i][j] = 0;
				}
			}
		}

		printf("#%d %d\n", t, max_result);
		max_result = 0; max_high = 0; 
	}

	return 0;
}
