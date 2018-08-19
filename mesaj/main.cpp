#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
FILE *f=fopen("mesaj.in","r");
FILE *g=fopen("mesaj.out","w");
short dp[1605];
int N,M;
char C[1005][24];
short len[1605];
char V[1605];
short ppoz[1005][24];
vector<int> poz[1005][26];
inline short mini(short a,short b)
{
    return a<b ? a:b;
}
int main()
{
    fscanf(f,"%d%d\n",&M,&N);
    fgets(V+1,1605,f);
    for(int i=1;i<=M;i++)
    {
        fgets(C[i]+1,24,f);
        len[i]=strlen(C[i]+1)-1;
        for(int j=len[i];j;j--)
            poz[i][C[i][j]-'a'].push_back(j);
    }
    for(int i=1;i<=N;i++)
    {
        dp[i]=dp[i-1]+1;
        for(int j=1;j<=M;j++)
        {
            ppoz[j][0]=i;
            for(auto it:poz[j][V[i]-'a'])
            {
                if(ppoz[j][it-1])
                {
                    ppoz[j][it]=ppoz[j][it-1];
                }
            }
            if(ppoz[j][len[j]])
                dp[i]=mini(dp[i],dp[ppoz[j][len[j]]-1]+i-len[j]-ppoz[j][len[j]]+1);
        }
    }
    fprintf(g,"%hd",dp[N]);
    fclose(f);
    fclose(g);
    return 0;
}
