
// 19236 청소년 상어 재귀함수, 백트래킹, DFS이용 13:02-
#include <iostream>
#include <algorithm>
using namespace std;

struct FISH{ int y,x,dir;};
int n; int map[4][4]; FISH fish[16]; int res{0};
int dy[] = {-1,-1,0,1,1,1,0,-1}; int dx[] = {0,-1,-1,-1,0,1,1,1};

void dfs(int map[4][4], FISH fish[16], int shark_y, int shark_x, int sum) {
    // 백트래킹복사한다
    int selected_map[4][4];
    FISH selected_fish[16];
    for(int y=0;y<4;y++){
        for(int x=0;x<4;x++) selected_map[y][x]= map[y][x];}
    for(int i=0;i<16;i++) selected_fish[i]= fish[i];
    
    //상어가 먹는다
    int eatten_fish= selected_map[shark_y][shark_x];
    int shark_dir= selected_fish[eatten_fish].dir;
    selected_fish[eatten_fish].y=-1; selected_fish[eatten_fish].x=-1;
    selected_fish[eatten_fish].dir=-1; selected_map[shark_y][shark_x]=-1 ;
        
    sum+=(eatten_fish+1);res= max(res, sum);
        
    // 물고기들이 움직인다
    for(int f=0;f<16;f++){
        //죽은얘는 상종안해!!!!!!!!!!
        if(selected_fish[f].y==-1) continue;
        
        int cy= selected_fish[f].y; int cx= selected_fish[f].x; int cd= selected_fish[f].dir;
        int ny= cy+dy[cd]; int nx= cx+dx[cd]; int nd=cd;
        while(ny>3||nx>3||nx<0||ny<0|| (ny==shark_y && nx==shark_x)){
            nd=(nd+1)%8; ny= cy+dy[nd]; nx= cx+dx[nd];}
        
        if(selected_map[ny][nx]!=-1){
            int next_fish= selected_map[ny][nx];
            
            // map
            selected_map[ny][nx]=f; selected_map[cy][cx]=next_fish;
            //물고기정보
            selected_fish[f].y= ny; selected_fish[f].x= nx; selected_fish[f].dir= nd;
            selected_fish[next_fish].y= cy; selected_fish[next_fish].x= cx;}
        
        else{
            selected_map[ny][nx]=f; selected_map[cy][cx]=-1;
            //물고기정보
            selected_fish[f].y= ny; selected_fish[f].x= nx; selected_fish[f].dir= nd;}}
    
    //상어가 이동한다
    for(int s=1;s<4;s++){
        int shark_ny= shark_y+ dy[shark_dir]*s; int shark_nx= shark_x+dx[shark_dir]*s;
        if(shark_ny>3|| shark_ny<0||shark_nx>3|| shark_nx<0) break;
        // !잊지마! 죽은얘가 아니면 dfs돌린다
        if(selected_map[shark_ny][shark_nx]!=-1){
            dfs(selected_map,selected_fish,shark_ny,shark_nx,sum);}}}

int main(){
    for(int y=0;y<4;y++){ int a,b;
        for(int x=0;x<4;x++){ cin>>a>>b;
            --a; --b; // 이해안가도 유의사항
            map[y][x]=a; fish[a].y=y; fish[a].x=x; fish[a].dir=b;}}
    dfs(map, fish,0,0,0); cout<<res<<"\n"; return 0;}
