
// BFS 최소환승경로 //
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
int n, m, s, e;
vector<int> adj[200001]; //입력
int ans[200001]; //출력

int bfs(){
    queue <int> q;
    ans[s] = 0;
    q.push(s);
    while(!q.empty()){
        int cur = q.front(); q.pop();
        
        if(cur == e) return ans[cur] - 1 > 0 ? ans[cur] - 1 : 0;
        
        for(auto next : adj[cur]) {
            
            if(ans[next] > -1) continue;
            if(next > 100000) ans[next] = ans[cur] + 1;
            else ans[next] = ans[cur];
            q.push(next);}}
        return -1;}

int main(){
    memset(ans,-1,sizeof(ans));
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        while(1){
            int v;
            cin >> v;
            if(v == -1) break;
            adj[v].push_back(i+100000);
            adj[i+100000].push_back(v);}}
    cin >> s >> e; cout << bfs(); }

