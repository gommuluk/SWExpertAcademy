/*
2383. [모의 SW 역량테스트] 점심 식사시간
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5-BEE6AK0DFAVl
*/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
#include <vector>
#define FIRST 1
#define SECOND 2
using namespace std;

typedef struct {
	int x, y;
	int first, second; // 문까지의 거리
} PERSON;

typedef struct {
	int x, y, len;
} STAIR;

int testcase, min_time;
int N, K, S; // K는 사람 수 , S는 계단 수
int map[11][11];
PERSON person[15]; // 입력 받는 사람
STAIR stair[5]; // 입력 받는 계단
int which_door[15]; // 사람 나눌 때 사용
int sub_time;
queue<int> fq, sq; // 각 계단에서 대기하는 사람들
vector<int> first_stair, second_stair; // 계단 내려가는 사람, 3명 제한

void DFS(int depth);
int go_to_eat(void);
void init();
void init_to_eat();

int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		init();
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 1) { // 사람이면
					K++;
					person[K].x = i, person[K].y = j;
				}
				else if (map[i][j]) { // 계단이면
					S++;
					stair[S].x = i, stair[S].y = j, stair[S].len = map[i][j];
				}
			}
		}

		// 사람들이 각 문에 도달하는 시간 계산해서 구조체에 저장
		for (int i = 1; i <= K; i++) {
			person[i].first = abs(person[i].x - stair[FIRST].x) + abs(person[i].y - stair[FIRST].y);
			person[i].second = abs(person[i].x - stair[SECOND].x) + abs(person[i].y - stair[SECOND].y);
			
		}

		//아래 주석들을 모두 풀고 돌리면 밑에 출력되는 것들이 다 0이 됩니다. 왜 그럴까요? 
		//which door랑 person이랑 아무런 관련도 없는데 왜 그럴까요.. 둘은 메모리를 공유하고 있는 걸까요?
		//memset은 함부로 쓰지 말아야 하나요?
		//printf("%d %d %d %d\n", person[1].x, person[1].y, person[1].first, person[1].second);
		//memset(which_door, 0, sizeof(PERSON) * 15);
		//printf("%d %d %d %d\n", person[1].x, person[1].y, person[1].first, person[1].second);
		DFS(1);
	
		printf("#%d %d\n", t, min_time);
	}
}

void init() {
	min_time = (1 << 30);
	K = 0, S = 0;
	memset(person, 0, sizeof(PERSON) * 15);
	memset(stair, 0, sizeof(STAIR) * 5);
	sub_time = 0;
}

void init_to_eat() {
	first_stair.clear();
	second_stair.clear();
	while (!fq.empty()) fq.pop();
	while (!sq.empty()) sq.pop();
}

void DFS(int depth) {
	if (depth > K) {
		sub_time = go_to_eat();
		if (min_time > sub_time) min_time = sub_time;
		return;
	}
	
	which_door[depth] = FIRST;
	DFS(depth + 1);
	which_door[depth] = SECOND;
	DFS(depth + 1);
}

int go_to_eat(void) {
	init_to_eat();
	int how_long = 0; // 시간
	int can_eat = 0; // 식당에 도착한 사람 수 
	PERSON tmp[15];
	
	for (int i = 1; i <= K; i++) {
		tmp[i].first = person[i].first; tmp[i].second = person[i].second;
		tmp[i].x = person[i].x; tmp[i].y = person[i].y;
		
	}

	while (can_eat < K) { // 사람들 다 내려갈 때까지 
		how_long++;

		if (!first_stair.empty()) { // 첫 번째 계단에 사람 있으면 내려보내라 
			for (int i = first_stair.size() - 1; i >= 0; i--) {
				first_stair[i]--;
				if (!first_stair[i]) { // 수가 0이 되면
					first_stair.erase(first_stair.begin() + i); // 벡터에서 제거
					can_eat++; // 식당 도착
				}
			}
		}
		if (!second_stair.empty()) { // 두 번째 계단에 사람 있으면 내려보내라 
			for (int i = second_stair.size() - 1; i >= 0; i--) {
				second_stair[i]--;
				if (!second_stair[i]) {
					second_stair.erase(second_stair.begin() + i);
					can_eat++; // 식당 도착
				}
			}
		}

		// 이 과정을 통해 계단에서 1분 기다렸다가 내려가게 하는 조건을 만족..해..
		while (!fq.empty() && first_stair.size() < 3) { // 대기 중인 사람부터 들어가세요
			first_stair.push_back(stair[FIRST].len);
			fq.pop();
		}
		while (!sq.empty() && second_stair.size() < 3) { // 세 명 밖에 못 올라가는 계단이 어딨겠냐만은..
			second_stair.push_back(stair[SECOND].len);
			sq.pop();
		}

		for (int i = 1; i <= K; i++) { // 아직 사무실인 사람 둠칫둠칫 움직이는 중
			if (which_door[i] == FIRST) {
				tmp[i].first--;
				if (!tmp[i].first) { // 계단에 도착하면
					tmp[i].x = 0, tmp[i].y = 0; // 내 정보를 스윽 지우고
					fq.push(i); // 대기탄다..
				}
			}
			else if (which_door[i] == SECOND){
				tmp[i].second--;
				if (!tmp[i].second) {
					tmp[i].x = 0, tmp[i].y = 0;
					sq.push(i);
				}
			}
		}
	}

	return how_long;
}
