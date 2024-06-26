#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("trecere.in","r");
FILE *g=fopen("trecere.out","w");
int L[125][125];
int C[125][125];
int E=99999999,ef;
int x,y;
int N;
int M;
int i,j,val,col;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&val);
            L[val][++L[val][0]]=i;
            C[val][++C[val][0]]=j;
        }
    }
    for(i=1;i<=M;i++)
    {
        sort(L[i]+1,L[i]+1+N);
        sort(C[i]+1,C[i]+1+N);
        nth_element(C[i]+1,C[i]+(N+1)/2,C[i]+N+1);
        col=C[i][(N+1)/2];
        ef=0;
        for(j=1;j<=N;j++)
        {
            ef=ef+abs(col-C[i][j])+abs(j-L[i][j]);
        }
        if(ef<E)
        {
            E=ef;
            x=i;
            y=col;
        }
    }
    fprintf(g,"%d %d %d",E,x,y);
    fclose(f);
    fclose(g);
    return 0;
}
