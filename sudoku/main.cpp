#include <cstdio>
using namespace std;
FILE *f=fopen("sudoku1.in","r");
FILE *g=fopen("sudoku1.out","w");
unsigned long long l;
long long valori,V[40][40],j,i,N,K;
long long a;
int main()
{
    fscanf(f,"%lld %lld",&N,&K);
    l=(1<<(N-1));
    l*=(1<<(N-1));
    l*=3;
    fprintf(g,"%llu\n",l);
    l/=3;
    if(K<=l) V[1][1]=1;
    else if(K<=2*l) {V[1][1]=2;K-=l;}
    else {V[1][1]=3;K-=2*l;}
    for(i=2;i<=N;i++)
    {
        l/=2;
        if(K<=l)
        {
            if(V[1][i-1]==1)
                V[1][i]=2;
            else
                V[1][i]=1;
        }
        else
        {
            K-=l;
            if(V[1][i-1]==3)
                V[1][i]=2;
            else
                V[1][i]=3;
        }
    }
    for(i=2;i<=N;i++)
    {
       l/=2;
       if(K<=l)
       {
           if(V[i-1][1]==1)
                V[i][1]=2;
           else
            V[i][1]=1;
       }
       else
       {
           K-=l;
           if(V[i-1][1]==3)
            V[i][1]=2;
           else
            V[i][1]=3;
       }
    }
    for(i=2;i<=N;i++)
    {
        for(j=2;j<=N;j++)
        {
            if(V[i-1][j]==V[i][j-1])
            {
                V[i][j]=(1^2^3^V[i][j-1]^V[i-1][j-1]);
            }
            else
            {
                V[i][j]=(1^2^3^V[i-1][j]^V[i][j-1]);
            }
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
            fprintf(g,"%lld ",V[i][j]);
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
