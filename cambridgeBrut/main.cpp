#include <cstdio>
#include <algorithm>
using namespace std;
int N,M;
int T[100005];
int D[100005];
bool cmp(int a,int b){
    return D[a] < D[b];
}
int main(){
    freopen("in","r",stdin);
    freopen("ok","w",stdout);
    scanf("%d %d",&N,&M);
    for(int i = 1;i <= N;i++){
        scanf("%d %d",&T[i],&D[i]);
    }
    while(M--){
        int x,y;
        scanf("%d %d",&x,&y);
        vector<int> tmp;
        for(int i = x;i <= y;i++){
            tmp.push_back(i);
        }
        sort(tmp.begin(),tmp.end(),cmp);
        long long sumT = 0;
        bool ok = 1;
        for(auto it:tmp){
            sumT += T[it];
            if(sumT >= D[it]){
                ok = 0;
                break;
            }
        }
        printf("%d\n",ok);
    }
    return 0;
}
