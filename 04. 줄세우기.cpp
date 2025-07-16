


// 2252 줄세우기 DAG-큐다
#include<iostream>
#include<vector>
#include<queue>
#define INF 987654321
#define MAX 32001
using namespace std;
int inDegree[MAX]; vector<int> adj[MAX]; int n;

void DAG(){
    queue<int> q;
    for(int i=1;i<=n;i++) if(inDegree[i]==0) q.push(i);
    while(!q.empty()){
        int cur= q.front(); cout<<cur<<" "; q.pop();
        for(int next: adj[cur]){
            inDegree[next]--;
            if(inDegree[next]==0) q.push(next);}}}
       
int main(){
    int m; cin>>n>>m;
    while(m--){
        int a,b; cin>>a>>b; adj[a].push_back(b); inDegree[b]++;}
    DAG(); return 0;}
    





