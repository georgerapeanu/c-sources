#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("zebughil.in","r");
FILE *g=fopen("zebughil.out","w");
pair<int,int> dp[1<<17];
int N,G;
int V[20];
int main()
{
    for(int t=1;t<=3;t++)
    {
        fscanf(f,"%d %d",&N,&G);
        dp[0].first=1;
        for(int i=1;i<=N;i++)fscanf(f,"%d",&V[i]);
        for(int i=1;i<(1<<N);i++)dp[i]={1<<30,0};
        for(int i=0;i<(1<<N);i++)
        {
            for(int j=1;j<=N;j++)
            {
                if((i>>(j-1))&1);
                else
                {
                    pair<int,int> rez=dp[i];
                    if(rez.second+V[j]<=G)rez.second+=V[j];
                    else rez={dp[i].first+1,V[j]};
                    dp[i|(1<<(j-1))]=min(dp[i|(1<<(j-1))],rez);
                }
            }
        }
        fprintf(g,"%d\n",dp[(1<<N)-1].first);
    }
    fclose(f);
    fclose(g);
    return 0;
}
