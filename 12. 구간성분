// 10840 구간 성분 해싱
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
// #include <map>
// #include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    string sa, sb; cin >> sa>>sb;
    int a_size = (int)sa.size(),b_size = (int)sb.size();
    set<vector<int>> hash; // vector<int>의 크기가 버킷사이즈다

    for (int y = 0; y < a_size; y++){ vector<int> alpha(26);
        for (int x = y; x < a_size; x++) {
            alpha[sa[x] - 'a']++;
            hash.insert(alpha);}}
        
    int res = 0;
    for (int y = 0; y < b_size; y++) { vector<int> alpha(26);
        for (int x = y; x < b_size; x++) {
            alpha[sb[x] - 'a']++;
            if (hash.count(alpha)>0) res = max(res, x-y+1);}}
    cout << res; return 0;}



