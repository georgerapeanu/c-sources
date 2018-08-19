#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("siruri2.in","r");
FILE *g=fopen("siruri2.out","w");
int N,M,i,j,cost;
char c1[505];
char c2[505];
int L[505][505];
int main()
{
    c1[0]='.';
    c2[0]='.';
    fgets(c1+1,505,f);
    fgets(c2+1,505,f);
    N=strlen(c1)-1;
    M=strlen(c2)-1;
    for(i=0;i<=N;i++)
        L[i][0]=i;
    for(i=0;i<=M;i++)
        L[0][i]=i;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(c1[i]==c2[j])
                cost=0;
            else
                cost=1;
            L[i][j]=min(L[i-1][j-1]+cost,min(L[i][j-1]+1,L[i-1][j]+1));
        }
    }
    fprintf(g,"%d",L[N][M]);
    fclose(f);
    fclose(g);
    return 0;
}
