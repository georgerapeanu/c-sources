#include <cstdio>
#include <cstring>
#define MOD 666013
using namespace std;
FILE *f=fopen("frumusete.in","r");
FILE *g=fopen("frumusete.out","w");
int K,N,i,len,val,dp[1005][1005][2],j,rez;
char C[1005];
int main()
{
    fscanf(f,"%d\n",&N);
    dp[0][0][0]=1;
    for(i=1;i<=1000;i++)
    {
        for(j=0;j<=1000;j++)
        {
            dp[i][j][0]=(dp[i-1][j][1]+dp[i-1][j][0])%MOD;
            dp[i][j][1]=(dp[i-1][j-1][1]+dp[i-1][j][0])%MOD;
        }
    }
    while(N)
    {
        fscanf(f,"%d ",&K);
        fgets(C+1,1005,f);
        len=strlen(C+1);
        if(C[len]=='\n')
        len--;
        val=0;
        for(i=1;i<=len;i++)
        {
            if(C[i]=='1')
            {
                if(val<=K)
                    {rez+=dp[len-i][K-val][0]+dp[len-i][K-val][1];rez%=MOD;}
                if(C[i-1]=='1')
                    val++;
            }
        }
        N--;
        if(val==K)
            rez++;
        fprintf(g,"%d\n",rez);
        rez=0;
    }
    return 0;
}
