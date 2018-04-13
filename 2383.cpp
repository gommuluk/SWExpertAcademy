/*
2383. [���� SW �����׽�Ʈ] ���� �Ļ�ð�
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
	int first, second; // �������� �Ÿ�
} PERSON;

typedef struct {
	int x, y, len;
} STAIR;

int testcase, min_time;
int N, K, S; // K�� ��� �� , S�� ��� ��
int map[11][11];
PERSON person[15]; // �Է� �޴� ���
STAIR stair[5]; // �Է� �޴� ���
int which_door[15]; // ��� ���� �� ���
int sub_time;
queue<int> fq, sq; // �� ��ܿ��� ����ϴ� �����
vector<int> first_stair, second_stair; // ��� �������� ���, 3�� ����

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
				if (map[i][j] == 1) { // ����̸�
					K++;
					person[K].x = i, person[K].y = j;
				}
				else if (map[i][j]) { // ����̸�
					S++;
					stair[S].x = i, stair[S].y = j, stair[S].len = map[i][j];
				}
			}
		}

		// ������� �� ���� �����ϴ� �ð� ����ؼ� ����ü�� ����
		for (int i = 1; i <= K; i++) {
			person[i].first = abs(person[i].x - stair[FIRST].x) + abs(person[i].y - stair[FIRST].y);
			person[i].second = abs(person[i].x - stair[SECOND].x) + abs(person[i].y - stair[SECOND].y);
			
		}

		//�Ʒ� �ּ����� ��� Ǯ�� ������ �ؿ� ��µǴ� �͵��� �� 0�� �˴ϴ�. �� �׷����? 
		//which door�� person�̶� �ƹ��� ���õ� ���µ� �� �׷����.. ���� �޸𸮸� �����ϰ� �ִ� �ɱ��?
		//memset�� �Ժη� ���� ���ƾ� �ϳ���?
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
	int how_long = 0; // �ð�
	int can_eat = 0; // �Ĵ翡 ������ ��� �� 
	PERSON tmp[15];
	
	for (int i = 1; i <= K; i++) {
		tmp[i].first = person[i].first; tmp[i].second = person[i].second;
		tmp[i].x = person[i].x; tmp[i].y = person[i].y;
		
	}

	while (can_eat < K) { // ����� �� ������ ������ 
		how_long++;

		if (!first_stair.empty()) { // ù ��° ��ܿ� ��� ������ ���������� 
			for (int i = first_stair.size() - 1; i >= 0; i--) {
				first_stair[i]--;
				if (!first_stair[i]) { // ���� 0�� �Ǹ�
					first_stair.erase(first_stair.begin() + i); // ���Ϳ��� ����
					can_eat++; // �Ĵ� ����
				}
			}
		}
		if (!second_stair.empty()) { // �� ��° ��ܿ� ��� ������ ���������� 
			for (int i = second_stair.size() - 1; i >= 0; i--) {
				second_stair[i]--;
				if (!second_stair[i]) {
					second_stair.erase(second_stair.begin() + i);
					can_eat++; // �Ĵ� ����
				}
			}
		}

		// �� ������ ���� ��ܿ��� 1�� ��ٷȴٰ� �������� �ϴ� ������ ����..��..
		while (!fq.empty() && first_stair.size() < 3) { // ��� ���� ������� ������
			first_stair.push_back(stair[FIRST].len);
			fq.pop();
		}
		while (!sq.empty() && second_stair.size() < 3) { // �� �� �ۿ� �� �ö󰡴� ����� ����ڳĸ���..
			second_stair.push_back(stair[SECOND].len);
			sq.pop();
		}

		for (int i = 1; i <= K; i++) { // ���� �繫���� ��� ��ĩ��ĩ �����̴� ��
			if (which_door[i] == FIRST) {
				tmp[i].first--;
				if (!tmp[i].first) { // ��ܿ� �����ϸ�
					tmp[i].x = 0, tmp[i].y = 0; // �� ������ ���� �����
					fq.push(i); // ���ź��..
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
