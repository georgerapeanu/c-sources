#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
FILE *f = fopen("clepsidru.in","r");
FILE *g = fopen("clepsidru.out","w");
int V[1006];
int NV[1006];
int N,B,K,S,P;
int main()
{
    fscanf(f,"%d %d",&N,&B);
    fprintf(g,"%d\n",N + B - 1);
    fscanf(f,"%d",&K);
    N++;
    V[1] = B;
    while(K--){
        fscanf(f,"%d %d",&S,&P);
        memset(NV,0,sizeof(NV));
        if(P == 2){
            reverse(V + 1,V + 1 + N);
        }
        NV[1] = max(0,V[1] - S);
        for(int i = 2;i < N;i++){
            if(i > S){
                NV[i] = (V[i - S] > 0);
            }
            else {
                NV[i] = (i - 1 <= S && S <= i + V[1] - 2);
            }
            if(N - i <= S){
                NV[N] += V[i];
            }
        }
        NV[N] += V[N] + min(V[1],max(0, S - N + 2));
        memcpy(V,NV,sizeof(NV));
        if(P == 2){
            reverse(V + 1,V + 1 + N);
        }
    }
    if(P == 1){
        for(int i = 1;i < N - 1;i++){
            fprintf(g,"%d 0\n",V[i]);
        }
        fprintf(g,"%d %d\n",V[N - 1],V[N]);
    }
    else{
        fprintf(g,"%d %d\n",V[1],V[2]);
        for(int i = 2;i < N;i++){
            fprintf(g,"0 %d\n",V[i + 1]);
        }
    }
    return 0;
}
