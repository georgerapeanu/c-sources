#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("acces.in","r");
FILE *g=fopen("acces.out","w");
int a[1005][1005],S[1005][1005],i,j,N,M,Q,x,y;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&a[i][j]);
        }
    }
    for(i=1;i<=M;i++)
    {
        if(a[1][i]==0)
            S[1][i]=S[1][i-1]+1;
        else
            S[1][i]=0;
    }
    for(i=1;i<=N;i++)
    {
        if(a[i][1]==0)
            S[i][1]=S[i-1][1]+1;
        else
            S[i][1]=0;
    }
    for(i=2;i<=N;i++)
    {
        for(j=2;j<=M;j++)
        {
            if(a[i][j]==1)
           {
               if(S[i-1][j]<=0) S[i][j]=S[i-1][j];
               else if(S[i][j-1]<=0) S[i][j]=S[i][j-1];
               else S[i][j]=-1*S[i-1][j-1];
           }
           else
           {
               if(a[i-1][j]==0&&a[i][j-1]==0) S[i][j]=S[i][j-1]+S[i-1][j]-abs(S[i-1][j-1])+1;
               else if(a[i][j-1]==0)    S[i][j]=1+S[i][j-1];
               else if(a[i-1][j]==0) S[i][j]=1+S[i-1][j];
               else S[i][j]=1;
           }
        }
    }
    fscanf(f,"%d",&Q);
    for(i=1;i<=Q;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        fprintf(g,"%d\n",S[x][y]);
    }
    fclose(f);
    fclose(g);
    return 0;
}

