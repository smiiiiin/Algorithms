// 3830 교수님은 기다리지 않는다
/*
 종료는 0 0
 샘플 개수 n ||   ?!횟수: m
 ! a b w    == b가a보다 w그램 무겁다
 ? a b     b가 얼마나 무겁니?
 
 1 2 10
 2 3 10
 4 3 15
----------
 ? 1 3 cout<< 20;
 ? 4 1 cout<< -5;
 */
#include <iostream>
using namespace std;
#define MAX 100001
typedef long long ll;
int n, m, root[MAX]; ll diff[MAX];

int find(int x){
    if(root[x]==x) return x;
    int R = find(root[x]);
    // Root 까지 비용 업데이트
    diff[x] += diff[root[x]];
    return root[x]=R;
}
//1 2 10 2가 1보다 10크다 2= 1+10 ;
void join(int a, int b, int dif){
    int aRoot = root[a]; int bRoot = root[b];
    if(aRoot == bRoot) return;
    
    //int NewD = diff[a] + dif;
    //int OriginD = diff[b];
    diff[bRoot] = (diff[a] + dif) -diff[b];
    //join의 주목적: root를 교체= join
    root[bRoot] = aRoot;}

int main(){ ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);
while(1){
    cin >> n >> m; if(n==0&&m==0) break;
    
    for (int i = 1; i <= n; ++i){
        root[i] = i;
        diff[i] = 0;}
    
    for (int i = 0; i < m; ++i){
        char ch; int a, b, w;
        cin >> ch >> a >> b;
        find(a); find(b);
        
        if(ch == '!'){ cin >> w; join(a,b,w);}
        else{
            if(root[a]==root[b]) cout << diff[b] - diff[a] << '\n';
            else cout << "UNKNOWN" << '\n';}}}
return 0;}


