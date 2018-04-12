/*
2117. [���� SW �����׽�Ʈ] Ȩ ��� ����
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V61LqAf8DFAWu
*/

#include <cstdio>
#include <cmath>
using namespace std;

int testcase, N, M;
int map[25][25];
int cost[25]; // �� K�� ���� ���
int max_house, max_cost, service_house, max_service_house;
int K; // ó�� ������ ������� ũ��
int tmp_i;

int main() {
	scanf("%d", &testcase);

	// ȸ�� ������ ������ ����� ���� ����Ѵ�. 
	for (int k = 1; k <= 22; k++) { // �Է����� ���� �� �ִ� N�� �ִ밪�� 20�̹Ƿ� K�� �ִ밪�� 22�� �ȴ�.
		cost[k] = k * k + (k - 1)*(k - 1);
	}
	
	for (int t = 1; t <= testcase; t++) {
		scanf("%d %d", &N, &M);
		for (int i = 1; i <= N; i++) { // ���� �Է� ����
			for (int j = 1; j <= N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j]) max_house++;
			}
		}

		max_cost = max_house * M; // (��ü ���) * (��ü �� ��) = �������� �� �� �ִ� �ִ� ���
		for (int k = 1; k <= 22; k++) { // �ִ� ��뺸�ٴ� ���� ������ ���� �� �� �����Ƿ� �ش��ϴ� K�� ã�´�
			K = k - 1;
			if (cost[k] > max_cost) break;
		}

		while (K > 0) { // ���� ū K���� K�� 1�� �� ������ Ž��			
			for (int a = 1; a <= N; a++) { // a�� b�� ���� ������ �߽� ��ǥ�̴�.
				for (int b = 1; b <= N; b++) { // �߽� ��ǥ�� (0,0)���� (N,N)���� Ž���� ����

					for (int j = (-1)*(K - 1); j <= (K - 1); j++) { // �� �߽������� ���� ���� Ž��..
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
			else K--; // ���� ������ ���δ�
		}

		//���ظ� ���� �����鼭 Ȩ��� ���񽺸� ���� ���� ���鿡 �����ϴ� ���� ������ ã���� ��, �� ���� ���񽺸� ���� �޴� ������ ��
		printf("#%d %d\n", t, max_service_house);
		max_house = 0; service_house = 0, max_service_house = 0;
	}
	return 0;
}
