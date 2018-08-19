#include <cstdio>
using namespace std;
FILE *f=fopen("android.in","r");
FILE *g=fopen("android.out","w");
int intre[25][25][25],i,j,N,M,y,x1,y1,x2,y2;
long long l,config,S;
int dp[25][1050000];
double a,b,x;
bool gasit;
void copie(int x,int y,int z)
{
    for(int i=0;i<=intre[x][y][0];i++)
    {
        intre[x][z][i]=intre[x][y][i];
    }
    intre[x][z][++intre[x][z][0]]=z;
}
bool ok(long config,int i,int j)
{
    for(int k=2;k<intre[i][j][0];k++)
        if(config&(1<<intre[i][j][k])==0)
            return false;
    return true;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N*M;i++)
    {
        intre[i][i][0]=1;
        intre[i][i][1]=i;
        for(j=i+1;j<=N*M;j++)
        {
            x1=(j-1)%M+1;
            y1=(j-1)/M+1;
            x2=(i-1)%M+1;
            y2=(i-1)/M+1;
            x1=x1-1;
            y1=N-y1;
            x2=x2-1;
            y2=N-y2;
            a=x2-x1;
            b=y2-y1;
            if(b==0)
            {
                copie(i,j-1,j);
            }
            else if(a==0)
            {
                copie(i,j-M,j);
            }
            else
            {
                y=y2-1;
                gasit=0;
                while(!gasit)
                {
                    x=((y-y1)/b)*a+x1;
                    if(x==int(x))
                    {
                        gasit=1;
                    }
                }
                copie(i,(N-y)*M+x,j);
            }

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
                if((config&(1<<(j-1)))!=0&&ok(config,i,j)==1)
                {
                    dp[config][i]+=dp[config-(1<<(i-1))][j];
                    dp[config][i]%=666013;
                }
            }
            S+=dp[config][i];
            S%=666013;
        }
    }
    for(i=1;i<l;i++)
    {
        for(j=1;j<=N*M;j++)
            fprintf(g,"%d ",dp[i][j]);
        fprintf(g,"\n");
    }
    fprintf(g,"%d",S);
    fclose(f);
    fclose(g);
    return 0;
}
