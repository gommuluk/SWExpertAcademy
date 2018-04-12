/*
2477. [���� SW �����׽�Ʈ] ���� �����
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV6c6bgaIuoDFAXy
*/

#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

int testcase, result = 0;
int N, M, K, A, B;
int reception[10], repair[10], arrive_time[1111]; 
int reception_customer_num[10], repair_customer_num[10];
int customer_time[1111];
int cnt = 0, top = 1, finish, it;
queue<int> recep_q, rep_q, answer_q;
bool answer_tf[1111];

int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		scanf("%d %d %d %d %d", &N, &M, &K, &A, &B);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &reception[i]);
		}
		for (int i = 1; i <= M; i++) {
			scanf("%d", &repair[i]);
		}
		for (int i = 1; i <= K; i++) {
			scanf("%d", &arrive_time[i]);
		}

		cnt = arrive_time[1]; // cnt �ʱ�ȭ�� ù �մ�����!

		while (finish < K) { // ���� ���� �����ҰԿ�~
			while (top <= K) {// ����â�� ��� �մ� ��Ű���?
				if (arrive_time[top] == cnt) { // ��ó׿�
					recep_q.push(top); // �ϴ� ť���� ������ּ��� 
					top++;
				}
				else break;
			}

			for (it = 1; it <= N; it++) { // �� â���� �ִ��� �����Կ�~
				if (!reception_customer_num[it] && !recep_q.empty()) { // ���� ���� â������.. ���� ������� !
					int tmp = recep_q.front(); // ����� �մ� �ӽù�ȣ�� ������ �����
					recep_q.pop();

					reception_customer_num[it] = tmp; // â���� ���ǰԿ�~
					customer_time[tmp] = reception[it]; // ����� �ɷ¸�ŭ ����ϽǰŰ��
					if (it == A) answer_tf[tmp] = true; // �մ� Ȥ�� A�� â�� �̿���̽ø�.. ��������
				}
				else if (reception_customer_num[it]) { // �� ������� �ð��� �� ����������~
					int go = reception_customer_num[it]; // �� â���� ��� ���� �մ� ��ȣ�� ������ �����
					customer_time[go]--; // �մ� �ð��� ���Ѱڽ��ϴ�
					if (!customer_time[go]) {
						rep_q.push(go);  // ���� â�� �� ������ �մ��� ���� â������ ����ϽǰԿ�~
						reception_customer_num[it] = 0; // â�� ������ϴ�
						it--; // �� â�� ������� ���� �մ� �����Կ�~
					}
				}
			}

			//�ư� ���� â�� �� ä����~ ����� ��ġ�� �� ������ �����̴ϱ�^^
			for (it = 1; it <= M; it++) { // �� â���� �ִ��� �����Կ�~
				if (!repair_customer_num[it] && !rep_q.empty()) { // ���� ���� â������.. ���� ������� !
					int tmp = rep_q.front(); // ����� �մ� �ӽù�ȣ�� ������ �����
					rep_q.pop();

					repair_customer_num[it] = tmp; // â���� ���ǰԿ�~
					customer_time[tmp] = repair[it]; // ����� �ɷ¸�ŭ ����ϽǰŰ��
					if (it == B && answer_tf[tmp]) {
						answer_q.push(tmp); // �մ� Ȥ�� A~B�� â�� �̿���̽ø�.. �������� (����)
					}
				}
				else if (repair_customer_num[it]) { // �� ������� �ð��� �� ����������~
					int go = repair_customer_num[it]; // �� â���� ��� ���� �մ� ��ȣ�� ������ �����
					customer_time[go]--; // �մ� �ð��� ���Ѱڽ��ϴ�
					if (!customer_time[go]) {
						repair_customer_num[it] = 0; // �ȳ��������� �մ�
						finish++; // (�� �� ���´�!)
						it--; // �� â�� ������� ���� �մ� �����Կ�~
					}
				}
			}

			cnt++; // ������ ������ 1�ʰ� �������ϴ�
		}

		//�մ� �� ���´�^^
		if (answer_q.empty()) result = -1;
		else {
			while (!answer_q.empty()) {
				result += answer_q.front(); // A�� B�� �̿��� ������ ����ȣ�� ��
				answer_q.pop();

			}
		}
		
		printf("#%d %d\n", t, result);
		result = 0; top = 1; finish = 0;
		memset(answer_tf, 0, 1111);
	}
	return 0;
}