
// BFS>QUEUE> 16236 아기상어
/* !! q는 기본 틀 유지하고 pop();기준으로 방송출연(visited=1, 행동)
 소개해주기 전이나 생방 전에는 필수로 new_face인지 아닌지 보기 */
// n, map이 주어진다 1-6물고기크기, 아기상어, 빈칸, 자기보다 크지 않으면 지나가고 작아야 먹는다
// 먹는 순, 최단거리, y위 x위
#include <iostream>
#include <queue>
using namespace std;

int n; int dy[] = {-1, 0, 0, 1}, dx[] = {0, -1, 1, 0};
int map[20][20]; // bool  visited[20][20];

struct FISH{ int y,x,time;
    bool operator<(const FISH f)const{
        if(f.time==time){
            if(f.y==y) return f.x<x;
            return f.y<y;}
        return f.time<time;}
    FISH(int a,int b, int c){ y=a; x=b; time=c;}
};

queue<FISH> q;

int bfs(){
    int res=0, eat=0,size=2;
    // q안에 pq이용하려고 q밖에 while(1)쓰고 쓰자마자 pq선언, visited도 바로
    while (1){
        priority_queue<FISH> pq; bool visited[20][20]={0,};
            
        while (!q.empty()){
            int cy= q.front().y;int cx= q.front().x;int ct= q.front().time; q.pop();
            for(int d=0;d<4;d++){
                int ny = cy+ dy[d]; int nx= cx+dx[d];
                if(ny>=n||nx>=n||ny<0||nx<0) continue;
                if(visited[ny][nx]|| map[ny][nx]>size) continue;
                visited[ny][nx]=1;
                q.push(FISH(ny,nx,ct+1)); // 필터망
                if(map[ny][nx]<size && map[ny][nx]!=0){
                    pq.push(FISH(ny,nx,ct+1));}}}
        
        // 이제 q가 비면 pq타임(먹는다) 이 시작된다
        if(pq.empty()) break;
        
        int eatten_cy=pq.top().y; int eatten_cx=pq.top().x;
        int eatten_ct=pq.top().time; // pq.pop();   //pop을 하면 왜 안될까?
        
        eat++; if(eat== size){ size++; eat=0;}
        map[eatten_cy][eatten_cx]=0;
        // 다시 q로 넣는다 먹을땐 시간 0소요 ?
        q.push(FISH(eatten_cy,eatten_cx,0));
        res+= eatten_ct;}
    return res;}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n; for(int y=0;y<n;y++){
                for(int x=0;x<n;x++){
                        cin>>map[y][x];
                        if(map[y][x]==9){
                            map[y][x]=0; q.push({y,x,0});}}}
    cout<<bfs()<<"\n"; return 0;}
