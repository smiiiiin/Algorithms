
//백준1644 소수의 연속합 : 큐로
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

int main(void) {
    int ans; vector<bool> check; vector<int> prime;
    scanf("%d", &ans);
    check.resize(ans + 1, true);

    //소수만들기
    for(int i=2;i*i<=ans;i++){ //i는 루트 n까지만 보면 된다.
        for(int j=i; i*j <=ans;j++){
            //check인덱스 안에 들어가는 수 i*j가 <=n일때까지
            check[i*j]=0;}}

    for (int i = 2; i <= ans ; i++) {
            if (check[i]) prime.push_back(i);}

    queue<int> q; int sum{0},cnt{0};
    
    for(int i=0;i<prime.size();i++) {
        q.push(prime[i]); sum+=prime[i];
        while(sum>ans) {int cur= q.front(); sum-=cur; q.pop();}
        if(sum==ans) cnt++;}
    
    printf("%d", cnt);
    return 0;
}
