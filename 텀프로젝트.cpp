// 백준 9466 텀 프로젝트
#include <iostream>
#include <cstring>
#define MAX 100001
using namespace std;
int t,n; int arr[100001]; int visited[100001]; int cnt;

void dfs(int cur){
    if(visited[cur]==-1) visited[cur]=1;
    int next= arr[cur];
    if(visited[next]==-1) dfs(next);
    else if(visited[next]!=2){
            for(int i=next; i!=cur;i=arr[i]) cnt++;
            cnt++;}
        visited[cur]=2;}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> t; while (t--) { //초기화
        cnt = 0; memset(visited, -1, sizeof(visited));
        cin >> n; for (int i = 1; i <= n; i++) cin >> arr[i];
        for (int i = 1; i <= n; i++) dfs(i);
        cout << n-cnt << '\n';} return 0;}

