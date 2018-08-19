#include <cstdio>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;
FILE *f = fopen("moft.in","r");
FILE *g = fopen("moft.out","w");
priority_queue<int> H;
int lst[200005];
int nxt[200005];
set<pair<int,int> > S;
int ans;
int S,N;
int K[1005];
int sz;
int t,T;
void reset(){
    S.clear();
    while(!H.empty()){
        H.pop();
    }
}
int main()
{
    fscanf(f,"%d %d",&t,&T);
    while(T--){
        reset();
        fscanf(f,"%d %d",&N,&S);
        for(int i = 1;i <= S;i++){
            fscanf(f,"%d",&K[i]);
        }
        for(int i = 1;i <= N;i++){
            H.push(-i);
        }
        sz = 0;
        for(int i = 1;i <= N;i++){

        }
    }
    return 0;
}
