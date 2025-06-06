#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("android.in","r");
FILE *g=fopen("android.out","w");
int intre[25][25],i,j,N,M,y,X1,Y1,X2,Y2,L[25][25];
long long l,config,S;
int dp[1050000][25];
double a,b,x;
bool gasit;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N*M;i++)
    {
        intre[i][i]=(1<<(i-1));L[i][i]=i;
        for(j=i+1;j<=N*M;j++)
        {
            X1=(j-1)%M+1;
            Y1=(j-1)/M+1;
            X2=(i-1)%M+1;
            Y2=(i-1)/M+1;
            a=X2-X1;
            b=Y2-Y1;
            if(b==0)
            {
                intre[i][j]=intre[i][j-1]+(1<<(j-1));
                L[i][j]=max(L[i][j-1],j);
            }
            else if(a==0)
            {
                intre[i][j]=intre[i][j-M]+(1<<(j-1));
                L[i][j]=max(L[i][j-M],j);
            }
            else
            {
                y=Y1-1;
                gasit=0;
                while(!gasit)
                {
                    x=((y-Y1)/b)*a+X1;
                    if(x==int(x))
                    {
                        gasit=1;
                    }
                    y--;
                }
                intre[i][j]=intre[i][int(y*M+x)]+(1<<(j-1));
                L[i][j]=max(L[i][int(y*M+x)],j);
            }
            intre[j][i]=intre[i][j];
            L[j][i]=L[i][j];
        }
    }
    l=1<<(N*M);
    for(i=1;i<=N*M;i++)
      dp[0][i]=1;
    for(config=1;config<l;config++)
    {
        for(i=1;i<=N*M;i++)
        {
           if((config&(1<<(i-1)))!=0)
            for(j=1;j<=N*M;j++)
            {
                if((config&(1<<(j-1)))!=0&&(intre[i][j]&config)==intre[i][j])
                {
                    dp[config][i]+=dp[config-(1<<(i-1))][j];
                    dp[config][i]%=666013;
                }
            }
            S+=dp[config][i];
            S%=666013;
        }
    }
    fprintf(g,"%lld",S);
    fclose(f);
    fclose(g);
    return 0;
}
