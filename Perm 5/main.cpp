#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
FILE *f=fopen("perm5.in","r");
FILE *g=fopen("perm5.out","w");
vector<int> P,R;
bool E[2005];
double dp[2005][305];
int ant[2005][305];
double loga[2005];
int N;
int main()
{
    fscanf(f,"%d",&N);
    P.push_back(0);
    for(int i=2;i<=N;i++)
    {
        if(!E[i])
        {
            P.push_back(i);
            loga[i]=log(i);
            for(int j=i*i;j<=N;j+=i)
                E[j]=1;
        }
    }
    for(int i=1;i<=N;i++)ant[i][0]=1;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<P.size();j++)
        {
            dp[i][j]=dp[i][j-1];
            ant[i][j]=0;
            double lg=0;
            for(int len=1;len<=i;len*=P[j],lg+=loga[P[j]])
            {
                if(dp[i][j]<dp[i-len][j-1]+lg)
                {
                    dp[i][j]=dp[i-len][j-1]+lg;
                    ant[i][j]=len;
                }
            }
        }
    }
    int x=N,y=P.size()-1;
    while(x)
    {
        if(ant[x][y])R.push_back(ant[x][y]);
        x-=ant[x][y];y-=(y!=0);
    }
    sort(R.begin(),R.end());
    int last=0;
    for(auto it:R)
    {
        int tmp=++last;
        for(int i=1;i<it;i++)
            fprintf(g,"%d ",++last);
        fprintf(g,"%d ",tmp);
    }
    fclose(f);
    fclose(g);
    return 0;
}
