#include <cstdio>
#include <algorithm>
using namespace std;
int N,M,m[210][210],i,j;
FILE *f=fopen("pion.in","r"),*g=fopen("pion.out","w");
int main()
{
    fscanf(f,"%d%d",&M,&N);
    for(i=1;i<=N;i++)
    fscanf(f,"%d",&m[M+1][i]);
    for(i=1;i<=M;i++)
    fscanf(f,"%d",&m[i][N+1]);
    fclose(f);
    for(i=M;i>0;i--)
    {
        for(j=N;j>0;j--)
        {
            if((i+j)%2==0)
            {
                m[i][j]=max(m[i+1][j],m[i][j+1]);
            }
            else
            {
                m[i][j]=min(m[i+1][j],m[i][j+1]);
            }
        }
    }
    fprintf(g,"%d",m[1][1]);
    fclose(g);
    return 0;
}