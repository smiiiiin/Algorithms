
// 백준 11438 LCA 2 : 입력, 부모, depth 순으로
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#define MAX 18 // 10^5 < 2^17이므로 17까지만 보면됨
using namespace std;
int n,m;
vector<int> adj[100001];
int parents[100001][MAX];
int depth[100001];

void depth_bfs(){ // 노드의 깊이+ 1번째 직계부모
    queue<int> q;
    q.push(1); depth[1]=0;
    while(!q.empty()){
        int cur= q.front(); q.pop();
        for(auto next: adj[cur]){
            if(depth[next]!=-1) continue;
            depth[next]= depth[cur]+1;
            parents[next][0]= cur;
            q.push(next);}}}

int main(){ios_base::sync_with_stdio(false); cout.tie(0); cin.tie(0);
    cin>>n; int a,b; // root노드는 1번노드
    for(int i=1;i<n;i++){ cin>>a>>b; adj[a].push_back(b);
        adj[b].push_back(a); }
    // 초기화
    memset(parents,-1,sizeof(parents)); memset(depth,-1,sizeof(depth));
    depth_bfs();
    for(int x=0;x< MAX;x++) parents[1][x]=0;
    // parents[][] 채우기 : 2^(x+1) (좌) = 2^x + 2^x (우) : 할머니(좌)= 부모의 부모(우)
    for(int x=1;x< MAX;x++){ // !!! 밑으로 쭉쭉내리면서 채워야한다 채우는 순서도 중요
                             // 자식노드가 부모,조상노드 번호보다 클거라는 보장이 없기 때문
        for(int y=2;y<=n;y++){
            if(parents[y][x]==-1)
                parents[y][x]= parents[parents[y][x-1]][x-1];}}
    // depth차 구하고 맞춰 올리기
    cin>>m; int c,d; while(m--){cin>>c>>d;int tmp;
        if(depth[c]<depth[d]){tmp=c; c=d; d=tmp;} //c가 아래오도록 설정
        int diff= depth[c]-depth[d];
        for(int r=0;diff;r++){
            if(diff&1) c= parents[c][r]; //c를 d까지의 depth와 같을때까지 올리기
            diff>>=1;}// 10=1010(2) 1과 3에서 r을 살려
        // 최종 LCA구하기
        while(c!=d){ int r;
            for(r=0;r< MAX;r++){
                if(parents[c][r]== parents[d][r]) break;}
            if(r!=0) r--;
            c= parents[c][r]; d= parents[d][r];}
        cout<<c<<'\n';} return 0;}
