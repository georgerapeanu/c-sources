#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("royfloyd.in","r");
FILE *g=fopen("royfloyd.out","w");
int N;
int cost[105][105];
void royfloyd()
{
    for(long long k=1;k<=N;k++)
    {
        for(long long i=1;i<=N;i++)
        {
            if(i!=k)
            {
                for(long long j=1;j<=N;j++)
                {
                    if(i!=j&&j!=k)
                    {
                        cost[i][j]=min(cost[i][k]+cost[k][j],cost[i][j]);
                    }
                }
            }
        }
    }
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)for(int j=1;j<=N;j++){fscanf(f,"%d",&cost[i][j]);if(!cost[i][j])cost[i][j]=1<<29;}
    royfloyd();
    for(int i=1;i<=N;i++,fprintf(g,"\n"))for(int j=1;j<=N;j++)fprintf(g,"%d ",cost[i][j]==1<<29 ? 0:cost[i][j]);
    fclose(f);
    fclose(g);
    return 0;
}
