


/* Rabin-Karp_1605*/
/* 포인트  (라빈카프(롤링해시) + 패러매트릭 서치) 문제
 "가장 긴 문자열(3033)"과 같은 문제임.. (코드 같음)
*/
#include <iostream>
using namespace std;
#define MAX_LEN 200010
#define MOD 300007
#define NODE_SIZE MAX_LEN
#define HASH_SIZE MOD
typedef long long ll;

// 전역변수
char temp[MAX_LEN];
int L, ans;
int nodeCnt;

// 함수선언
void ParametricSearch();
bool Rabin_Karp(int);
int Mod(ll);

typedef struct Node{
    int index;
    Node* next;
    
    Node(){
        index = -1;
        next = nullptr;
    }
    Node* alloc(int index, Node* next){
        this->index = index;
        this->next = next;
        return this;
    }
}Node;

Node nodePool[NODE_SIZE];

typedef struct Hash{
    Node* hashTable;  // (Node 배열)을 저장... 포인터배열대신.. 노드로 생성하는게 "더미노드"역할해서.. 코드가 더 간결해짐 (포인터변수 사용하면 코드에서 null인경우 고려해서 추가코딩해야함)
    
    // 해싱함수(Key2Index())는.. 외부에서 처리하게끔하고. (이전 해시값과 비교해야하므로) 여기서는 해당인덱스에 연결만함
    void insert(int hashIndex, int index){
        Node* prev = &hashTable[hashIndex];
        prev->next = nodePool[nodeCnt++].alloc(index, prev->next);
    }
    Node* operator[](int hashIndex){
        if(hashIndex < 0 || hashIndex >=HASH_SIZE) return nullptr;
        return &hashTable[hashIndex];
    }
    Hash(){
        hashTable = new Node[HASH_SIZE];  // 이렇게.. 동적할당하면. Node()생성자에 의해서 초기화 되므로.. 수동으로 매번 init(), for문 이용해서 nullptr 넣는 것 보다 더 빠를듯?
    }
    ~Hash(){
        delete[] hashTable;  // Rabin_Karp() 종료될때마다. 메모리 해제.
    }
}Hash;

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    
    // 입력부
    cin>>L;
    cin>>temp;
    
    // 실행부
    ParametricSearch();

    // 출력부
    if(ans==-1) cout<<0<<"\n";  // 문자열이 없는 경우
    else cout<<ans<<"\n";  // 문자열이 있는 경우

    return 0;
}

void ParametricSearch()
{
    int left=0, right=L-1, mid;  // 가능---mid---불가능,  ("가능"한 최대 mid값 구해야함)
    bool res;
    
    while(1)
    {
        mid = (left+right)/2;
        res = Rabin_Karp(mid);
        if( res) left  = mid+1;
        if(!res) right = mid-1;
    
        if(left > right){ans=left-1;  break;}
    }
}

bool Rabin_Karp(int M)  // (길이 M) 단위로 (길이 L)인 문자열을 확인해봄.
{
    nodeCnt=0;  // 초기화 해주어야함.. ㅠ.ㅠ.. 항상 nodeCnt는 Hash같은 구조체들 보다 먼저 초기화해주자..
    Hash pos;
    int hash=0;
    ll power=1;

    // 실행부
    for(int i=0; i<=L-M; i++)  // 문자열의 "맨 왼쪽" 인덱스
    {
        // 실행부 (해시값 생성)
        if(i==0)  // "Mod()연산을 수행하기 때문에".. 길이M에 따라서.. 해시값이 달라질 수 있다.. 따라서 새로운M에 대해서 매번 새로운 해시값을 계산해야함.. (DP 못씀)
        {
            for(int j=0; j<M; j++)  // 문자열 길이 M만큼 탐색해서. 해시값 만든다.
            {
                hash = Mod(hash + 1LL*temp[M-1 -j]*power);  // 맨오른쪽 인덱스부터. 가중치(power) 1 곱해주고 누적함..
                if(j < M-1) power = Mod(power<<1);      // power값이 2^(M-1)까지만 만들어지도록함. j=0~M-1로 M번 연산하면 2^M 되버리니까.. 2^M-1 만들기 위해서 M-1번만 연산함
            }
        }
        else hash = Mod( ((hash -1LL*temp[i-1]*power)<<1) + temp[M-1 +i]);  // (이전해시값 - 맨왼쪽 위치값)*2 + (맨오른쪽 위치값) -> *2는.. 각 위치가 한칸 이동하면 모든 위치가 *2 되니까.
    
        // 실행부 (해시값 충돌 확인)
        if( pos[hash]->next != nullptr )  // 해시충돌한 경우 (앞전에 나온 문자열이 있는 경우)
        {
            Node* prev = pos[hash];
            
            // 충돌 일어난 "문자열들 갯수"만큼 모두 확인.
            while(1)
            {
                if(prev->next == nullptr) break;
                
                // 앞전에나온 문자열(해시에 등록된)과 현재문자열 비교
                bool res = true;
                int startIndex = prev->next->index;
                for(int j=startIndex, k=i;  j<startIndex+M;  j++,k++) if( temp[j] != temp[k] ){res=false;  break;}
                if(res == true) return true;
                
                prev = prev->next;
            }
        }
        else pos.insert(hash, i);  // 해시충돌하지 않은 경우 (해시테이블인덱스, 문자열 시작인덱스) 저장.
    }
    
    return false;
}

int Mod(ll n){
    if(n>=0) return n%MOD;  // 양수인 경우
    return ( (-n/MOD + 1)*MOD + n)%MOD;  // 양수가 아닌 경우
}



