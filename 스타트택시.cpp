
//  BFS 19238 스타트택시 -아기상어랑 비슷한 느낌ㅣ| q>>pq 걸러서>> q로 다시 넣기
/*  m명 데려다주기, n*n크기, 최단경로로만이동(가까운얘, 행, 열 작은순으로) struct pq이용
    연료는 이동할때마다 소모(=시간, 거리, 연료), 목적지로 태우면 그 승객한테 쓴 시간만큼 2배 충전
    >> 성공여부와 남은 연료양 출력 */
#include<iostream>
#include <queue>
#include<map>
using namespace std;
#define MAX 20
int dy[]= {-1,1,0,0}; int dx[]= {0,0,-1,1};

struct STATE{int y,x,gas; // (=gas,거리, 시간)
    bool operator<(const STATE s)const{
        if(s.gas==gas){
            if(s.y==y) return s.x<x;
            return s.y<y;}
        return s.gas>gas;}};
    
int n,m,gas; int pan[MAX][MAX];
map<pair<int,int>, pair<int,int>> goal;

bool sucess(pair<int,int> start){
    pair<int,int> destination = goal[start];
    
    queue<pair<STATE,int>> q; // q에 ((y,x,연료), 충전거리)
    q.push({{start.first, start.second, gas},0});
    bool visited[MAX][MAX]={false,};
    visited[start.first][start.second]= true;
    
    while(!q.empty()){
        int cy=q.front().first.y; int cx=q.front().first.x; int cg= q.front().first.gas;
        int charging= q.front().second; q.pop();
        
        if(cg==-1) return false;
        
        if(cy==destination.first&& cx== destination.second){
            gas= cg+ charging*2; return true;}
        
        for(int d=0;d<4;d++){
            int ny= cy+ dy[d]; int nx= cx+ dx[d];
            if(ny<0|| nx<0|| ny>=n|| nx>=n) continue;
            if(visited[ny][nx]|| pan[ny][nx]) continue;
            visited[ny][nx]=true;
            q.push({{ny,nx,cg-1},charging+1});}
    }
    return false;}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>m>>gas;
    for(int y=0;y<n;y++){
        for(int x=0;x<n;x++) cin>>pan[y][x];}
    
    pair<int,int> start; // 드라이버의 출발지
    cin>>start.first>>start.second;
    start.first--; start.second--; //cin>>하고 나서 --
    
    for(int i=0; i<m; i++){ //손님마다
        int y,x,y2,x2;
        cin>>y>>x>>y2>>x2; //cin>>하고 나서 --
        goal[{y-1,x-1}]= {y2-1, x2-1}; } //인덱스는 출발, 값은 목적
        
    while(1){ //pq를 q안에서 이용하려고 while(1) 사용
        priority_queue<STATE> pq;
        pq.push({start.first, start.second,gas});
        
        bool visited[MAX][MAX]={0, };
        visited[start.first][start.second]=true;
        bool flag= false;
        
        while(!pq.empty()){
            int y= pq.top().y; int x= pq.top().x; int cur_gas= pq.top().gas;
            pq.pop();
            
            if(cur_gas==-1) break;
            if(goal.count({y,x}) && goal[{y,x}].first!=-1){
                start={y,x}; flag= 1; gas=cur_gas; break;
            }
            for(int d=0;d<4;d++){
                int ny=y+dy[d]; int nx=x+dx[d];
                
                if(ny<0|| nx<0|| ny>=n|| nx>=n) continue;
                if(visited[ny][nx]|| pan[ny][nx]) continue;
                visited[ny][nx] = true; //한칸이동으로 인한 연료소모 -1
                pq.push({ ny, nx, cur_gas - 1 });}
        }
        
        if (flag == false) {cout << -1 << "\n"; return 0;}
        if (sucess(start) == false) {cout << -1 << "\n"; return 0;}
        if (--m == 0) {cout << gas << "\n"; return 0;}
        pair<int, int> temp = start; //시작위치와 -1,-1를 swap
        start = goal[{start.first, start.second}];
        goal[{temp.first, temp.second}] = { -1, -1 };
         }
    return 0;}

