// 2098 외판원 순회 : 순회는 어디서 시작하는지 중요하지 않아=> 1-4-3-2의 합= 4-3-2-1의 합
// 주의 사항 2가지 주석처리
#include<iostream>
#include<algorithm>
#include<cstring>
#define INF 987654321
#define MAX 16
using namespace std;
int weight[MAX][MAX]; int dp[MAX][1<<MAX]; int n;

int tsp(int idx, int visited){
    if(visited ==(1<<n)-1){
        if(weight[idx][0]!=0) return weight[idx][0];
        return INF;}
    
    // 이해 안되도 일단 외운 3줄
    int& ret= dp[idx][visited];
    if(ret!= -1) return ret;
    ret= INF;
     
    for(int i=0;i<n;i++){ // !! tsp(idx+1이 아니라 다음에 찍을 i를 택해야한다
        if(visited & (1<<i) || weight[idx][i]==0) continue;
        ret= min(ret,tsp(i, visited| (1<<i))+weight[idx][i]);}
    
    return ret;}

int main(){
    cin>>n; memset(dp, -1, sizeof(dp)); //이거 또 기억 못함;;
    for(int y=0;y<n;y++){
                for(int x=0;x<n;x++) cin>>weight[y][x];}
    cout<<tsp(0,1)<<"\n"; return 0;}
ㄴ
