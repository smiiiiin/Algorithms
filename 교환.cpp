
// 삼성 백준 1039 교환
/*
 정수 n, m은 n의 자리수 k번
 m보다 작은 숫자 i, j를 골라 순서를 바꾼다 단,맨 앞에 0이 오면 안된다
 k번 수행 시, !!최대값!!
 cin>>n>>k;
 단, k번 연산 못하면 -1출력
 
 132 3번 바꿔서 최대
 321 만들기 312 321 312

 */
#include<iostream>
#include<algorithm> //swap
#include<string>
#include<queue>
#include<cstring>
using namespace std;

queue<pair<string, int> > q;
int visited[1000001][11];
int main(){
    memset(visited, 0, sizeof(visited));
    string str;
    int k, ans=0;
    cin >> str >> k;
    
    q.push({str,0});
    while(!q.empty()){
        string fir= q.front().first; int sec= q.front().second; q.pop();
        
        if(sec == k) { // K번 연산했을 경우
            ans = max(ans, stoi(fir));
            continue;
        }
        
        for(int i=0; i<fir.size()-1; i++){
            for(int j=i+1; j<fir.size(); j++){
                swap(fir[i], fir[j]);
                
                // 맨앞이 0 이거나 이미 나온적이 있으면
                if(fir[0] == '0' || visited[stoi(fir)][sec+1]) {
                    swap(fir[i], fir[j]); // 다시 되돌려줌
                    continue;
                }
                q.push({fir, sec+1}); //swap한 string, 연산횟수+1
                visited[stoi(fir)][sec+1] = 1;
                swap(fir[i], fir[j]); // 다시 되돌려줌
            }
        }
    }
    if(ans == 0) cout << "-1";
    else cout << ans;
}

