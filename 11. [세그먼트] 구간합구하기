

// 2042 구간 합 구하기: 세그먼트 트리 (update가 잦고 구간합 구할 때)
#include <iostream>
using namespace std;
const int MAX= 1<<20; // 2^20 은 노드크기 1000000과 비슷하니까 = 리프노드 크기
long long tree[2*MAX]; // 트리의 크기는 리프*2;

void update(int idx, long long val) {
    int n= idx+MAX; // idx를 리프노드 idx로 변경 후에
    tree[n]=val; // 직계부모부터 루트노드까지 거슬러 올라가며 update
    for(n/=2; n;n/=2) tree[n]= tree[2*n]+tree[2*n+1];}

long long sum(int n, int start, int end, int from, int to) {
    if(from>end || start>to ) return 0;
    if(from<=start && end<=to) return tree[n]; // tree[n]으로 return 하기
    int mid= (start+ end)/2;
    return sum(2*n, start,mid,from,to)+sum(2*n+1, mid+1, end, from, to);}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n,m,k; cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>tree[MAX+i];
    // 채워진 leaf노드 바탕으로 바닥부터 루트 1번노드까지 값을 채운다
    for(int i=MAX-1; i; i--) tree[i]= tree[2*i]+tree[2*i+1]; m+=k;
    while(m--){int a,b; long long c;
        cin>>a>>b>>c;
        if(a==1) update(b,c); //tree는 0부터 있다
        else cout<<sum(1,0,MAX-1,b,c)<<'\n';}return 0;}
 
