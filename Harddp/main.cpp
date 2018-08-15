#include <cstdio>
using namespace std;
FILE *f=fopen("harddp.in","r");
FILE *g=fopen("harddp.out","w");
int T;
int N;
char C[1005];
char rez[1005];
int dp[1005][1005];
bool lafel[1005][1005];
int Z,U;
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d\n",&N);
        fgets(C+1,1005,f);
        Z=U=0;
        for(int i=1;i<=N;i++)
        {
            if(C[i]=='0')Z++;
            else         U++;
        }
        if(Z<U)for(int i=1;i<=N;i++)fprintf(g,"0");
        else   for(int i=1;i<=N;i++)fprintf(g,"1");
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
