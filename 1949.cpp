/*
1949.[PROBLEM] [���� SW �����׽�Ʈ] ���� ����
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
queue<Pos> q; //���츮 ��ǥ ����
Pos p;
bool visit[10][10]; // DFS �湮 ����
int x_move[4] = { -1,0,1,0 }, y_move[4] = { 0,-1,0,1 };
bool K_flag = false; //���� ����
int result; //�׷��� ����

void DFS(int x, int y) {

	visit[x][y] = true;
	result++; 

	for (int i = 0; i < 4; i++) {
		int x_next = x + x_move[i], y_next = y + y_move[i]; //���� ��ǥ ã��
		if (x_next < 1 || x_next > N || y_next < 1 || y_next > N) continue; 

		if (!visit[x_next][y_next]) { //�湮���� ���� ���� ���� 
			if (K_flag) { //���� ���� �ִٸ�
				if (matrix[x_next][y_next] < matrix[x][y]) // ���̻� ���� �� �����Ƿ� �⺻ ���Ǹ� üũ
					DFS(x_next, y_next);
			}
			else { //���� ���� ���ٸ� �� ���� �� �־�
				if (matrix[x_next][y_next] < matrix[x][y]) 
					DFS(x_next, y_next);
				else { 
					for (int k = 1; k <= K; k++) { //���� ��� ��� �����մϴ�.. �ִ��� ���ƾ� ���� �������
						if (matrix[x_next][y_next] - k < matrix[x][y]) {
							matrix[x_next][y_next] -= k;
							K_flag = true; //����
							DFS(x_next, y_next);
							matrix[x_next][y_next] += k;//����ġ
							K_flag = false;
						}						
					}
				}
			}			
		} 
	} 
	
	if (max_result < result) max_result = result; //�ִ밪 ����
	result--;
	visit[x][y] = false;
}

int main() {

	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {

		//�Է�
		scanf("%d %d", &N, &K);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &matrix[i][j]);
				if (max_high < matrix[i][j]) max_high = matrix[i][j];
			}
		}

		//�ְ� ���츮 ã��
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