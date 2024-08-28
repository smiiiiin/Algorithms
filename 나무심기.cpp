// 1280 나무심기
#include <iostream>
#include <vector>
using namespace std;
#define MAX 200004
#define ll long long

const ll mod = 1e9 + 7; int n, value; ll ret = 1, _prev;

vector<ll> tree_cnt(MAX, 0), tree_sum(MAX, 0);

ll _sum(vector<ll> &tree, int idx){ ll _ret = 0;
    while(idx){
        _ret += tree[idx];
        idx -= (idx & -idx);} return _ret;}

ll sum(vector<ll> &tree, int s, int e){
    if(s > e) return 0;
    return (_sum(tree, e) - _sum(tree, s - 1));}

void update(vector<ll> &tree, int idx, ll value){
    while(idx <= MAX){
        tree[idx] += value;
        idx += (idx & -idx);} return;}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n; for(int i = 1; i <= n; i++){
        cin >> value; value++;
        if(i != 1){
            ll left = value * sum(tree_cnt, 1, value - 1) - sum(tree_sum, 1, value - 1);
            ll right = sum(tree_sum, value + 1, MAX) - value * sum(tree_cnt, value + 1, MAX);
            ret *= (left + right) % mod;
            ret %= mod;}
        
        update(tree_cnt, value, 1);
        update(tree_sum, value, value);}
    cout << ret << "\n";}

