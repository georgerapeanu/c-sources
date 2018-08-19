#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("mts.in","r");
FILE *g=fopen("mts.out","w");
int N,K;
int T,t;
int maxim;
int S[200005];
int X[200005];
int main()
{
    fscanf(f,"%d%d%d",&N,&K,&T);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&S[i]);
        S[i]+=S[i-1];
    }
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&X[i]);
    }
    int j=N;
    for(int i=K;i;i--)
    {
        while(2*(X[K]-X[i])+X[j]-X[K]+S[j]-S[i-1]>T)
            j--;
        maxim=max(maxim,j-i+1);
    }
    j=1;
    for(int i=K;i<=N;i++)
    {
        while(2*(X[i]-X[K])+X[K]-X[j]+S[i]-S[j-1]>T)j++;
        maxim=max(maxim,i-j+1);
    }
    fprintf(g,"%d",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
