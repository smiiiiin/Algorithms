
//백준 3108 로고

#include<iostream>
#define MAX 2001
using namespace std;
 
int n; int map[MAX][MAX]; int dy[4] = { -1,1,0,0 }; int dx[4] = { 0,0,-1,1 };
 
void dfs(int y, int x){
    if(y<0||x<0||y>=MAX||x>=MAX) return;
    if(map[y][x]==2||map[y][x]==0) return;
    map[y][x]=2;
    for(int d=0;d<4;d++){
        int ny= y+dy[d]; int nx= x+dx[d]; dfs(ny,nx);
    }}
 
int main(void){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>n; int a,b,c,d;
    for(int i=0;i<n;i++) {cin>>a>>b>>c>>d;
    
    a= (a+500)*2; b= (b+500)*2; c= (c+500)*2; d= (d+500)*2;
    
    for(int i=b; i<=d; i++){
        map[i][a]=1; map[i][c]=1;
    }
    for(int i=a; i<=c; i++){
        map[b][i]=1; map[d][i]=1;
    }}

    int ret{0};
    for(int y=0;y<MAX;y++){
        for(int x=0;x<MAX;x++){
            if(map[y][x]==1) {dfs(y,x); ret++;}
        }
    }
    
    if (map[1000][1000]==2) ret--;
    cout<<ret<<"\n";
    
    return 0; }
