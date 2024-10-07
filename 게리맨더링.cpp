
// 4-c 17471 게리맨더링
// 인구수 차이의 최소화
#include <iostream>
#include <vector>

using namespace std;
const int INF = 987654321;
int n, a[11], m, temp, ret = INF, comp[11], visited[11];
vector<int> adj[11];

pair<int, int> dfs(int here, int value){
    visited[here] = 1;
    pair<int, int> ret = {1, a[here]};
    for(int there : adj[here]){
        if(comp[there] != value) continue; //색이 다르면
        if(visited[there]) continue; //색이 같으면 이어나간다
        pair<int, int> _temp = dfs(there, value);
        ret.first += _temp.first;
        ret.second += _temp.second;
    } return ret;}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n; for(int i = 1; i <= n; i++) cin >> a[i];
    
    for(int y = 1; y <= n; y++){
        cin >> m;
        for(int x = 0; x < m; x++){
            cin >> temp; //양방향간선
            adj[y].push_back(temp);
            adj[temp].push_back(y);}}
    
    for(int i = 1; i < (1 << n) - 1; i++){ //비트마스킹
        fill(comp, comp + 11, 0);
        fill(visited, visited + 11, 0);
        int idx1 = -1, idx2 = -1; //
        for(int j = 0; j < n; j++){
            if(i & (1 << j)){comp[j + 1] = 1; idx1 = j + 1;}
            else idx2 = j + 1;
        }
        pair<int, int> comp1 = dfs(idx1, 1); //시작점이 다르다
        pair<int, int> comp2 = dfs(idx2, 0);
        if(comp1.first + comp2.first == n) ret = min(ret, abs(comp1.second - comp2.second)); // 2개로 정확히 쪼개진다면 누락되는게 없다는 뜻
    }
    cout << (ret == INF ? -1 : ret)<< "\n";
}
