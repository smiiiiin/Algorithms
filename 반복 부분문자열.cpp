#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n, m;
vector<int> v[10001];
int depth[10001];
bool visited[10001];
int dfs(int i,int cnt) {
    depth[i] = cnt;
    int ret = cnt;
    int child = 0;
    for (int j : v[i]) {
        if (depth[j]) {
            ret = min(ret, depth[j]);
            continue;
        }
        child++;
        int prev=dfs(j, cnt + 1);
        if (depth[i] != 1 && prev >= cnt) {
            visited[i] = 1;
        }
        ret = min(ret, prev);
    }
    if (depth[i] == 1 && child >= 2)visited[i] = true;
    return ret;
}
int main(void) {
    ios::sync_with_stdio(false);    cin.tie(NULL);    cout.tie(NULL);
    cin >> n >> m;
    for (int i = 0, a,b; i < m; i++) {
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        if (!depth[i]) {
            dfs(i, 1);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++)if (visited[i + 1])ans++;
    cout << ans << '\n';
    for (int i = 0; i < n; i++)if (visited[i + 1])cout << i + 1 << " ";
    
    return 0;
}
