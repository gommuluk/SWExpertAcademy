/*
2105. [���� SW �����׽�Ʈ] ����Ʈ ī��
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5VwAr6APYDFAWu
*/

#include <cstdio>

int testcase, N;
int map[25][25], max_level = -1, level;
bool dessert[111], f;
int now_x, now_y;
int k;

int main() {
	
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &map[i][j]);
			}
		}

		//������ ��ǥ i,j
		for (int i = 1; i <= N; i++) {
			for (int j = 2; j <= N; j++) {
				//���� a,b
				for (int a = 1; a < N; a++) {
					for (int b = 1; b < N; b++) {

						// ������ �� ��ǥ nx,ny
						int nx[5] = { i, i + a,i + a + b,i + b, i };
						int ny[5] = { j, j + a,j + a - b,j - b, j };
							
						// ��ǥ�� ���� ���� �ֳ�
						for (k = 1; k < 4; k++) {
							if (nx[k]<1 || nx[k]>N || ny[k]<1 || ny[k]>N) break;
						}
						if (k != 4) break;
						
						// �� �𼭸��� ���� �� �̵� ����!
						now_x = nx[0], now_y = ny[0];
						for (int p = 1; p < 5; p++) {
							int type;
							while (now_x != nx[p]) {
								type = map[now_x][now_y];

								// ���� ����Ʈ ǥ�� �׸��Ծ�..
								if (!dessert[type]) dessert[type] = true;
								else { f = true; break; }

								if (p == 1) { now_x++; now_y++; }
								else if (p == 2) { now_x++; now_y--; }
								else if (p == 3) { now_x--; now_y--; }
								else if (p == 4) { now_x--; now_y++; }
							}
							//�߰��� �Ѱܳ� �Ŷ�� ���� �׸� ����
							if (f) break;
						}
						//���� �ʱ�ȭ
						f = false;
						for (int z = 1; z <= 100; z++) {
							dessert[z] = false;
						}

						if (now_x == nx[0]) {
							level = 2 * a + 2 * b;
							if (max_level < level) max_level = level;
						}							
					}
				}
			}
		}

		printf("#%d %d\n", t, max_level);
		max_level = -1;
	}
	return 0;
}