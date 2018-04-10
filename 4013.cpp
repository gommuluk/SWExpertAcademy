/*
4013. [모의 SW 역량테스트] 특이한 자석
https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWIeV9sKkcoDFAVH
*/

#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

class Turning {
public :
	int num;
	int way;

	Turning() {}
	Turning(int num, int way) {
		this->num = num;
		this->way = way;
	}
};

int testcase, result;
int K;
int magnet[5][10], pos[5];
queue<Turning> q;
Turning next_mag;
int a, b;
bool moving[5];

int main() {
	scanf("%d", &testcase);
	for (int t = 1; t <= testcase; t++) {
		scanf("%d", &K);
		for (int i = 1; i <= 4; i++) {
			for (int j = 0; j < 8; j++) {
				scanf("%d", &magnet[i][j]);
			}
		}
		for (int i = 0; i < K; i++) {
			scanf("%d %d", &a, &b);
			q.push(Turning(a, b));
		}
	
		//큐가 빌 때까지 돌리기
		while (!q.empty()) {
			next_mag = q.front();
			q.pop();
			moving[next_mag.num] = true;
			
			//현위치 자석보다 숫자가 작은 자석
			for (int i = 1; i < next_mag.num; i++) {
				if (magnet[next_mag.num - i][(pos[next_mag.num - i] + 2) % 8] != magnet[next_mag.num - (i - 1)][(pos[next_mag.num - (i - 1)] + 6) % 8]) {
					moving[next_mag.num - i] = true;
				}
				else break;
			}
			//현위치 자석보다 숫자가 큰 자석
			for (int i = 1; i <= 4 - next_mag.num; i++) {
				if (magnet[next_mag.num + i][(pos[next_mag.num + i] + 6) % 8] != magnet[next_mag.num + (i - 1)][(pos[next_mag.num + (i - 1)] + 2) % 8]) {
					moving[next_mag.num + i] = true;
				}
				else break;
			}



			//true인 자석을 돌린다..ㅅㅂ홀짝나눠 ㅅㅄㅄㅄㅂ
			for (int i = 1; i <= 4; i++) {
				if (moving[i]) {
					if ((i + next_mag.num) % 2 == 0) {
						pos[i] = (pos[i] - next_mag.way + 8) % 8;
					}
					else {
						pos[i] = (pos[i] + next_mag.way + 8) % 8;
					}
					moving[i] = false;
				}				
			}
		}

		// 점수 계산
		for (int i = 1; i <= 4; i++) {
			if (magnet[i][pos[i]] == 1) result += pow(2.0, (double)(i - 1));
			pos[i] = 0;
		}

		printf("#%d %d\n", t, result);
		result = 0;
	}
	return 0;
}