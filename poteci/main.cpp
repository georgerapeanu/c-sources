#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("poteci.in","r");
FILE *g=fopen("poteci.out","w");
int ss[1005][1005];
int sd[1005][1005];
int ds[1005][1005];
int dd[1005][1005];
int A[1005][1005];
int i,j,N,M,x,y,rez;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&A[i][j]);
            dd[i][j]=ss[i][j]=A[i][j];
            if((i!=N||j!=M)&&(i!=N||j!=M))
                sd[i][j]=ds[i][j]=ss[i][j];
            if((i==1&&j==M)||(i==N&&j==1))
                dd[i][j]=ss[i][j]=0;
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            ss[i][j]=max(ss[i-1][j]*(i!=2||j!=M),ss[i][j-1]*(i!=N||j!=2))+ss[i][j];
        }
        for(j=M;j>0;j--)
        {
            sd[i][j]=max(sd[i-1][j]*(i!=2||j!=1),sd[i][j+1]*(i!=N||j!=M-1))+sd[i][j];
        }
    }
    for(i=N;i>0;i--)
    {
        for(j=1;j<=M;j++)
        {
            ds[i][j]=max(ds[i+1][j]*(i!=N-1||j!=M),ds[i][j-1]*(i!=1||j!=2))+ds[i][j];
        }
        for(j=M;j>0;j--)
        {
            dd[i][j]=max(dd[i+1][j]*(i!=N-1||j!=1),dd[i][j+1]*(i!=1||j!=M-1))+dd[i][j];
        }
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            if(rez<ss[i][j]+sd[i][j]+ds[i][j]+dd[i][j]-2*A[i][j]&&!((i==1&&j==1)||(i==1&&j==M)||(i==N&&j==1)||(i==N&&j==M)))
            {
                rez=ss[i][j]+sd[i][j]+ds[i][j]+dd[i][j]-2*A[i][j];
                x=i;
                y=j;
            }
        }
    }
    fprintf(g,"%d\n%d %d",rez,x,y);
    fclose(f);
    fclose(g);
    return 0;
}
