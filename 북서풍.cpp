

// 5419 북서풍: Fenwick Tree
#include <iostream>
#include <algorithm>
#include <vector>
typedef long long ll;
using namespace std;

int n, x, y, t;
vector<int> tree, _y;
vector<pair<int, int>> a;

int sum (int idx){ int ret = 0;
    while(idx){
        ret += tree[idx];
        idx -= (idx & -idx);}
    return ret;}

void update(int idx, int value){
    while(idx <= n){
        tree[idx] += value;
        idx += (idx & -idx);}}

int find_index(const vector<int>& _y, int value){
    int ans{0}; int start = 0, en = _y.size() - 1;
    while(start <= en){
        int mid = (start + en) / 2;
        if(_y[mid] >= value) {en= mid-1; ans= mid;}
        if(_y[mid] < value) start = mid + 1;}
    return ans;}
    
int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >>t; while(t--){ cin >> n;
        // 초기화
        a.clear(); _y.clear(); tree.clear(); tree.resize(n + 1);
        for(int i = 0; i < n; i++){
            cin >> x >> y;
            a.push_back({x, -y});
            _y.push_back(-y);}
                        
        sort(a.begin(), a.end());
        sort(_y.begin(), _y.end());
        ll ret = 0;
        update(find_index(_y, a[0].second) + 1, 1);
        for(int i = 1; i < n; i++){
            int idx = find_index(_y, a[i].second) + 1;
            ret += 1LL * sum(idx);update(idx, 1);}
        cout << ret << "\n";} return 0;}

