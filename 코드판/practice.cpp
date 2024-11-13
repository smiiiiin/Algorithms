// 11438: LCA2
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

/*
 입력: 각 노드별로 연결된 트리! (그래프 아님, 그러나 이진트리도 아니여서 자식 많아도 됨)
 출력: 두개의 노드를 입력 시, LCA(최소공통부모노드) 출력
 !!! 2^n으로 저장하지 않으면, 최악의 경우 배열같이 일직선도 트리기 떄문이다. 그러면 10만번째 부모가 있을 수 있음.O(n)
 */

const int MAX = 18;  // 2^17까지 확인하기 때문에 18로 설정
const int NOODNUM = 100001;
vector<int> adj[NOODNUM];  // 트리의 인접 리스트
int depth[NOODNUM];        // 각 노드의 깊이
int parents[NOODNUM][MAX]; // 부모 배열: parents[노드][2^n번째 부모]


// BFS로 각 노드의 깊이와 1번째 부모를 설정
void depth_bfs() {
    queue<int> q; q.push(1);  depth[1] = 0;  // 루트 노드의 깊이는 0

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        for (auto next : adj[cur]) {
            if (depth[next] != -1) continue;  // 이미 방문한 노드는 건너뜀
            depth[next] = depth[cur] + 1;  // 다음 노드의 깊이는 현재 노드보다 1 더 큼
            parents[next][0] = cur;  // (2^0)1번째 부모는 현재 노드
            q.push(next);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n, m;  cin >> n; int a, b;
    //노드의 개수, 노드를 양방향 연결
    for (int i = 1; i < n; i++) {
        cin >> a >> b; adj[a].push_back(b); adj[b].push_back(a); }

    // 초기화
    memset(parents, -1, sizeof(parents));  // 부모 배열을 -1로 초기화
    memset(depth, -1, sizeof(depth));  // 깊이 배열을 -1로 초기화
    
    depth_bfs();

    // 부모 배열 채우기: (2^x)번째 부모 설정 = 트리라서 10만명이 있으면 최대부모가 log(10만)이다.
    for (int x = 1; x < MAX; x++) {
        for (int y = 1; y <= n; y++) {
            if (parents[y][x - 1] != -1) {
                parents[y][x] = parents[parents[y][x - 1]][x - 1];
            }
        }
    }

    //질문(쿼리)의 개수
    cin >> m;
    while (m--) { int c, d; cin >> c >> d;
        
        if (depth[c] < depth[d]) swap(c, d);  // c가 더 깊은 노드 (아래) 가 되도록 설정
        int diff = depth[c] - depth[d];
        // 아래의 쿼리가 찾을 때 빠르게 찾게해주는 요소 중 하나
        for (int i = 0; diff; i++) { // 1101(13)차이면 4번 묻는거임
            if (diff & 1) c = parents[c][i]; // 맨끝부터 읽는거임 1(올려야하냐)이냐?
            diff >>= 1; // 처리 완의 느낌 1101-> 110이 된다 >>오른쪽으로 한칸 미는 거니깐
        }

        // c와 d가 다르면 LCA를 찾기 위해 둘을 같은 레벨로 올림
        // 정보를 어떻게 변화시키는 가
        if (c != d) {
            for (int i = MAX - 1; i >= 0; i--) {
                if (parents[c][i] != parents[d][i]) {
                    c = parents[c][i];
                    d = parents[d][i];
                }
            }
            c = parents[c][0];  // 최종 LCA
        }

        cout << c << '\n';
    }

    return 0;
}


