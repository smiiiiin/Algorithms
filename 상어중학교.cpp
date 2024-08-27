
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int res = 0;
int N, M;
int board[20][20];

int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };

bool find_block();    //블록 찾기
void down();        //중력 작용
void rotate();        //반시계 회전

struct info {
    int x, y, cnt = 0, rainbowCnt = 0;
    // '<' 는 오름차순이다. 점점커지는 크레센도라 생각하기
    bool operator<(const info& i) const {
        if (cnt == i.cnt) {
            if (rainbowCnt == i.rainbowCnt) {
                if (x == i.x) return y < i.y; //뒤에 오는게 혹은 i가 우선순위가 높은 것이다.
                else return x < i.x;
            }
            else return rainbowCnt < i.rainbowCnt;
        }
        else return cnt < i.cnt;
    }
};

int main() {
    cin.tie(NULL); cout.tie(NULL); ios_base::sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }
    
    while (true) {
        int ret = find_block();
        if (!ret) break;            //블록이 없는 경우 종료
        down();
        rotate();
        down();
    }
    cout << res << '\n';

    return 0;
}

bool find_block() {
    bool visit[20][20] = { false, };
    priority_queue<info> pQ;

    // 블록을 찾아 priority queue에 삽입
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] > 0 && !visit[i][j]) {
                //이건왜해야하지?  굳이 visit과 rainvisit을 나누는 이유가뭐야-
                bool rainbowVisit[20][20] = { false, };
                queue<pair<int,int>> Q;
                Q.push({ i,j });
                visit[i][j] = true;

                int cnt = 1, rainbowCnt = 0;
                while (!Q.empty()) {
                    int x = Q.front().first;
                    int y = Q.front().second;
                    Q.pop();

                    for (int d = 0; d < 4; d++) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];

                        if (nx<0 || nx>N - 1 || ny<0 || ny>N - 1
                            || visit[nx][ny] || rainbowVisit[nx][ny]) continue;

                        if (board[nx][ny] == 0) {
                            rainbowVisit[nx][ny] = true;
                            Q.push({ nx,ny });
                            cnt++;
                            rainbowCnt++;
                        }
                        else if (board[i][j] == board[nx][ny]) {
                            visit[nx][ny] = true;
                            Q.push({ nx,ny });
                            cnt++;
                        }
                    }
                }

                pQ.push({ i,j,cnt, rainbowCnt });
            }
        }
    }

  // 더 이상 삭제할 블록이 없는 경우 false를 반환하고 main 함수 종료
    if (pQ.empty()) return false;

    // 가장 큰 블록 찾기
    int x = pQ.top().x;
    int y = pQ.top().y;
    int cnt = pQ.top().cnt;

    if (cnt < 2) return false;

    res += cnt * cnt;

    // 블록 삭제 작업 -> 삭제된 블록에는 BLANK(-2) 넣기
    queue<pair<int, int>> Q;
    Q.push({x,y });
    int blockId = board[x][y];
    board[x][y] = -2;

    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx<0 || nx>N - 1 || ny<0 || ny>N - 1) continue;

            if (board[nx][ny] == 0 ||  board[nx][ny]== blockId) {
                Q.push({ nx,ny });
                board[nx][ny] = -2;
            }
        }
    }

    return true;
}


void down() {
    for (int x = 0; x < N; x++) {
        for (int y = N - 1; y >= 0; y--) {
            if (board[y][x] == -2) {
                int ny = y;
                int nx = x;
                
                //일단 빈칸이고 0보다 크면 다 내려.
                while (ny > 0 && board[ny][nx]==-2) ny--;
                
                //이거 하려고 읽는 순서를 바꾼거다.
                //다
                if (board[ny][nx] == -1) continue;
                
                //상태변형이나 이동시에는 새로운 판을 만들거나, 임의의 수를
                //저장해놓을 변수를 만든다.
                board[y][x] = board[ny][nx];
                board[ny][nx] = -2;
            }
        }
    }
}

void rotate() { //rotation하면 어항정리 참고하면 너무 좋음
    int tempBoard[20][20];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = tempBoard[j][N-1-i];
        }
    }
}
