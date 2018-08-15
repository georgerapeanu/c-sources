#include <cstdio>
#include <algorithm>
using namespace std;
int T[20][400005];
long long MAXW[20][400005];
long long SUMW[20][400005],last;
int Q;
int N = 1;
int lvl[400005];
long long getFirstBig(long long node,long long W){
    for(int i = 19;i >= 0;i--){
        if(MAXW[i][node] < W){
            node = T[i][node];
        }
    }
    if(MAXW[0][node] >= W){
        return node;
    }
    return T[0][node];
}
void addNode(long long node,long long W){
    N++;
    node = getFirstBig(node,W);
    lvl[N] = lvl[node] + 1;
    T[0][N] = node;
    SUMW[0][N] = W;
    MAXW[0][N] = W;
    for(int i = 1;i < 20;i++){
        T[i][N] = T[i - 1][T[i - 1][N]];
        SUMW[i][N] = SUMW[i - 1][N] + SUMW[i - 1][T[i - 1][N]];
        MAXW[i][N] = max(MAXW[i - 1][N] , MAXW[i - 1][T[i - 1][N]]);
    }
}
long long qNode(long long node,long long W){
    long long ans = node,sum = 0;
    for(int i = 19;i >= 0;i--){
        int tmp = T[i][ans];
        if(sum + SUMW[i][ans] <= W){
            sum += SUMW[i][ans];
            ans = tmp;
        }
    }
    return lvl[node] - lvl[ans];
}
int main(){
    lvl[1] = 1;
    scanf("%d",&Q);
    while(Q--){
        long long t,l,r;
        scanf("%I64d %I64d %I64d",&t,&l,&r);
        l = l ^ last;
        r = r ^ last;
        if(t == 1){
            addNode(l,r);
        }
        else{
            printf("%I64d\n",(last = qNode(l,r)));
        }
    }
    return 0;
}
