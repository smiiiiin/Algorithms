
//백준 21608
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct student {
    int id;
    int lover[4];
    int x, y;
};

int N;
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

struct info {
    int x, y, blankCnt=0, friendCnt = 0;
    bool operator <(const info& i) const {
        if (friendCnt == i.friendCnt) {
            if (blankCnt == i.blankCnt) {
                if (x == i.x) return y > i.y;
                else return x > i.x;
            }
            else return blankCnt < i.blankCnt;
        }
        else return friendCnt < i.friendCnt;
    }
};


int satisfied[] = { 0,1,10,100,1000 };



int main() {
    cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);
    int board[20][20] = {0,};
    cin >> N;

    vector<student> students(N * N);
    for (int i = 0; i < N * N; i++) {
        cin >> students[i].id;
        for (int j = 0; j < 4; j++) {
            cin >> students[i].lover[j];
        }
    }

    // 1. 자리 배치하기
    for (int s = 0; s < N * N; s++) {
        priority_queue<info> pQ;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == 0) {
                    int blankCnt = 0, friendCnt = 0;
                    for (int d = 0; d < 4; d++) {
                        int nx = i + dx[d];
                        int ny = j + dy[d];

                        if (nx<0 || nx>N - 1 || ny<0 || ny>N - 1) continue;
                        if (board[nx][ny] == 0) blankCnt++;
                        else {
                            for (int k = 0; k < 4; k++) {
                                if (board[nx][ny] == students[s].lover[k]) {
                                    friendCnt++;
                                    break;
                                }
                            }
                        }
                    }
                    pQ.push({ i,j,blankCnt , friendCnt });
                }
            }
        }

        
            int x = pQ.top().x;
            int y = pQ.top().y;

            board[x][y] = students[s].id;
            students[s].x = x;
            students[s].y = y;
        
    }

    // 2. 만족도 계산
    int res = 0;
    for (int s = 0; s < N * N; s++) {
        int x = students[s].x;
        int y = students[s].y;

        int friends = 0;
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx<0 || nx>N - 1 || ny<0 || ny>N - 1) continue;
            for (int k = 0; k < 4; k++) {
                if (board[nx][ny] == students[s].lover[k]) {
                    friends++;
                    break;
                }
            }
        }
        res += satisfied[friends];
    }

    cout << res;

    return 0;
}
