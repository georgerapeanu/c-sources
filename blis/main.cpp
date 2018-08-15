#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("blis.in","r");
FILE *g=fopen("blis.out","w");
int dp[100005];
int K;
int N;
char C[100005];
int a,val;
vector<pair<int,int> > upd[100005];
int main()
{
    fscanf(f,"%d\n",&K);
    fgets(C+1,100005,f);
    N=strlen(C+1);
    fill_n(dp,100003,(1<<30)+69);
    dp[0]=-1;
    for(int i=1;i<=N;i++)
    {
        val=(val-(i>K ? ((C[i-K]-'0')<<(K-1)):0))*2+C[i]-'0';
        a=max(val,a);
        int nr=0;
        for(auto it:upd[i])
            dp[it.first]=min(dp[it.first],it.second);
        for(int j=i;j<i+K&&j<=N;j++)
        {
            nr=nr*2+C[j]-'0';
            int st=0,dr=100000;
            while(st<dr)
            {
                int mid=(st+dr+1)/2;
                if(dp[mid]>=nr)
                    dr=mid-1;
                else
                    st=mid;
            }
            if(nr<dp[st+1])
            {
                upd[j+1].push_back(make_pair(st+1,nr));
            }
        }
    }
    int val=(1<<30)+69;
    int st=0,dr=100000;
    while(st<dr)
    {
        int mid=(st+dr+1)/2;
        if(dp[mid]>=val)
            dr=mid-1;
        else
            st=mid;
    }
    fprintf(g,"%d\n%d",a,st);
    fclose(f);
    fclose(g);
    return 0;
}
