#include "bits/stdc++.h"

typedef long long ll;
ll a,b,c;

ll go(ll a, ll b){
    if(b==1) return a%c;
    ll ret = go(a,b/2);
    ret=(ret*ret)%c;
    if(b%2) ret= (ret*a)%c;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
    cout<<"a 입력: ";
    cin>>a;
    cout<<"b 입력: ";
    cin>>b;
    cout<<"c 입력: ";
    cin>>c;
    cout<<"result: "<<go(a,b)<<"\n";
    return 0;}
    
