#include <iostream>
#include <cstdio>
using namespace std;
int nrp = 666013;
int N,M;
long long sum = 0;
int main()
{
    scanf("%d %d",&N,&M);
    M -= (N - 1);
    printf("%d %d\n",nrp,nrp);
    for(int i = 1;i < N;i++){
        int cost = (nrp / (N - 1) + (i <= (nrp % (N - 1))));
        printf("%d %d %d\n",i,i + 1,cost);
    }
    int u = 1,v = 3;
    while(M--){
        printf("%d %d %d\n",u,v,(int)1e9);
        v++;
        if(v > N){
            u++;
            v = u + 2;
        }
    }
    return 0;
}
