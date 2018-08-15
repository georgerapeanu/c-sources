#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("centura.in","r");
FILE *g=fopen("centura.out","w");
int nr[100005];
int dp[33];
int N,M,K;
char C[100005];
int optim[33];
vector<int> poz;
int main()
{
    poz.push_back(0);
    fscanf(f,"%d %d %d\n",&N,&M,&K);
    fgets(C+1,100005,f);
    dp[0]=1;
    fill_n(optim+1,30,(1<<30));
    for(int i=1;i<=N;i++)
    {
        nr[i]=nr[i-1];
        if(C[i]=='A')
        {
            for(int j=0;j<poz.size();j++)
                if(nr[i]-nr[poz[j]]<=K)
               {
                   dp[poz.size()]+=dp[j];
                   optim[poz.size()]=min(optim[poz.size()],optim[j]+1);
               }
            poz.push_back(i);
        }
        else
            nr[i]++;
    }
    int rez=0,b=(1<<30);
    for(int j=0;j<poz.size();j++)
        if(nr[N]-nr[poz[j]]<=K)
            rez+=dp[j],b=min(optim[j],b);
    fprintf(g,"%d %d",rez,b);
    fclose(f);
    fclose(g);
    return 0;
}
