#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
int tmp[100005];
int left[100005];
int right[100005];
int ceva[100005];
int N;
int M;
void u(int pos,int val){
    for(;pos <= M + 1;pos += (-pos) & pos){
        ceva[pos] = max(ceva[pos],val);
    }
}
int q(int pos){
    int rez = 0;
    for(;pos;pos -= (-pos) & pos){
        rez = max(rez,ceva[pos]);
    }
    return rez;
}
int main()
{
    scanf("%d %d",&N,&M);
    tmp[1]++;tmp[M + 1]--;
    for(int i = 1;i <= N;i++){
        int S,D;
        scanf("%d %d",&S,&D);
        tmp[S]++;
        tmp[D + 1]--;
    }
    for(int i = 1;i <= M;i++){
        tmp[i] += tmp[i - 1];
    }
    memset(ceva,0,sizeof(ceva));
    int num0 = 0;
    for(int i = 1;i <= M;i++){
        left[i] = q(tmp[i]) + 1;
        u(tmp[i],left[i]);
    }
    memset(ceva,0,sizeof(ceva));
    for(int i = M;i;i--){
        right[i] = q(tmp[i]) + 1;
        u(tmp[i],right[i]);
    }
    int rez = 0;
    for(int i = 1;i <= M;i++){
        rez = max(rez,left[i] + right[i] - 1);
    }
    printf("%d",rez);
    return 0;
}
