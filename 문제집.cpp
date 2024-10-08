
#include<cstdio>
#include<queue>
#include<vector>
#define MAX 32004
using namespace std;
struct NODE{
    int n;
    NODE(int a){n=a;}
    bool operator<(const NODE a)const{
        return a.n<n;
    }
};
int main() {
    int n, m, inDegree[MAX + 1] = { 0 };
    vector<int> adj[MAX + 1];
    priority_queue<NODE> pq;
 
    scanf("%d%d", &n, &m);
    for (int i = 0 ; i < m; i++) {
        int a, b; scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        inDegree[b]++;}
 
    for (int i = 1; i <= n; i++)
        if (!inDegree[i]) pq.push(NODE(i));
 
    // 우선순위 큐를 이용하여 가장 노드의 번호가 앞에 있는 요소를 가져온다.
    // 현재 가능한 노드들 중에서는 번호가 가장 적은 문제를 먼저 풀어야 되기 때문이다.
    while (!pq.empty()) {
        int cur = pq.top().n; pq.pop(); printf("%d ", cur);
        for (auto next : adj[cur])
            if (--inDegree[next] == 0) pq.push(next);}
    
    return 0;}
