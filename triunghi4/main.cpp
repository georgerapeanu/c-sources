#include <cstdio>
#include <algorithm>
#define zeros(x) (x&(x^(x-1)))
using namespace std;
FILE *f=fopen("triunghi4.in","r");
FILE *g=fopen("triunghi4.out","w");
int V[1505][3005];
int T[1505][3005];
int N,M,P,x,y;
int AIB[3005];
void update(int poz,int val)
{
    for(int i=poz;i<3005;i+=zeros(i))
        AIB[i]+=val;
}
int query(int poz)
{
    int sum=0;
    for(int i=poz;i;i-=zeros(i))
        sum+=AIB[i];
    return sum;
}
int main()
{
    fscanf(f,"%d%d%d",&N,&M,&P);
    for(int i=1;i<=N;i++)
        for(int j=1;j<2*N;j++)
            V[i][j]=1;
    for(int i=1;i<=M;i++)
        fscanf(f,"%d %d",&x,&y),V[x][y]=0;
    for(int i=N;i;i--)
    {
        for(int j=1;j<=2*i-1;j+=2)
        {
            T[i][j]=min(T[i+1][j],T[i+1][j+2])*V[i+1][j+1]*V[i][j]+V[i][j];
            update(1,1);
            update(T[i][j]+1,-1);
        }
    }
    for(int i=1;i<=P;i++)
    {
        int val;
        fscanf(f,"%d",&val);
        fprintf(g,"%d\n",query(val));
    }
    return 0;
}
