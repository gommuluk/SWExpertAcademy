/*
2477. [모의 SW 역량테스트] 차량 정비소
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

		cnt = arrive_time[1]; // cnt 초기화는 첫 손님으로!

		while (finish < K) { // 오늘 영업 시작할게요~
			while (top <= K) {// 접수창구 대기 손님 계신가요?
				if (arrive_time[top] == cnt) { // 계시네요
					recep_q.push(top); // 일단 큐에서 대기해주세요 
					top++;
				}
				else break;
			}

			for (it = 1; it <= N; it++) { // 빈 창구가 있는지 가볼게요~
				if (!reception_customer_num[it] && !recep_q.empty()) { // 작은 수의 창구부터.. 만약 비었으면 !
					int tmp = recep_q.front(); // 행운의 손님 임시번호는 다음과 같고요
					recep_q.pop();

					reception_customer_num[it] = tmp; // 창구에 들어가실게요~
					customer_time[tmp] = reception[it]; // 담당자 능력만큼 대기하실거고요
					if (it == A) answer_tf[tmp] = true; // 손님 혹시 A번 창구 이용고객이시면.. 끄적끄적
				}
				else if (reception_customer_num[it]) { // 안 비었으면 시간을 좀 흘려보낼까요~
					int go = reception_customer_num[it]; // 이 창구에 상담 중인 손님 번호는 다음과 같고요
					customer_time[go]--; // 손님 시간좀 빼앗겠습니다
					if (!customer_time[go]) {
						rep_q.push(go);  // 접수 창구 일 끝나신 손님은 정비 창구에서 대기하실게요~
						reception_customer_num[it] = 0; // 창구 비었습니다
						it--; // 이 창구 비었으니 다음 손님 받을게요~
					}
				}
			}

			//아고 접수 창구 다 채웠네~ 힘들다 그치만 난 성실한 직원이니까^^
			for (it = 1; it <= M; it++) { // 빈 창구가 있는지 가볼게요~
				if (!repair_customer_num[it] && !rep_q.empty()) { // 작은 수의 창구부터.. 만약 비었으면 !
					int tmp = rep_q.front(); // 행운의 손님 임시번호는 다음과 같고요
					rep_q.pop();

					repair_customer_num[it] = tmp; // 창구에 들어가실게요~
					customer_time[tmp] = repair[it]; // 담당자 능력만큼 대기하실거고요
					if (it == B && answer_tf[tmp]) {
						answer_q.push(tmp); // 손님 혹시 A~B번 창구 이용고객이시면.. 끄적끄적 (씨익)
					}
				}
				else if (repair_customer_num[it]) { // 안 비었으면 시간을 좀 흘려보낼까요~
					int go = repair_customer_num[it]; // 이 창구에 상담 중인 손님 번호는 다음과 같고요
					customer_time[go]--; // 손님 시간좀 빼앗겠습니다
					if (!customer_time[go]) {
						repair_customer_num[it] = 0; // 안녕히가세요 손님
						finish++; // (한 명 보냈다!)
						it--; // 이 창구 비었으니 다음 손님 받을게요~
					}
				}
			}

			cnt++; // 오늘의 소중한 1초가 지났습니다
		}

		//손님 다 보냈다^^
		if (answer_q.empty()) result = -1;
		else {
			while (!answer_q.empty()) {
				result += answer_q.front(); // A와 B를 이용한 고객들의 고객번호의 합
				answer_q.pop();

			}
		}
		
		printf("#%d %d\n", t, result);
		result = 0; top = 1; finish = 0;
		memset(answer_tf, 0, 1111);
	}
	return 0;
}