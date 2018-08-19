#include <cstdio>
using namespace std;
FILE *f=fopen("harta5.in","r");
FILE *g=fopen("harta5.out","w");
typedef struct{int x1,x2,y1,y2;} cladire;
cladire V[1005];
int C[1505][1505];
int N,M,K,c;
int l;
bool A[1505];
bool B[1505];
int main()
{
    fscanf(f,"%d",&c);
    fscanf(f,"%d%d%d",&N,&M,&K);
    for(int i=1;i<=K;i++)
    {
        fscanf(f,"%d%d%d%d",&V[i].x1,&V[i].y1,&V[i].x2,&V[i].y2);
        C[V[i].x1][V[i].y1]++;C[V[i].x2+1][V[i].y2+1]++;C[V[i].x1][V[i].y2+1]--;C[V[i].x2+1][V[i].y1]--;
        if(V[i].x2-V[i].x1>1&&V[i].y2-V[i].y1>1){C[V[i].x1+1][V[i].y1+1]--;C[V[i].x2][V[i].y2]--;C[V[i].x1+1][V[i].y2]++;C[V[i].x2][V[i].y1+1]++;}
        if(V[i].x2-V[i].x1==V[i].y2-V[i].y1&&V[i].y2-V[i].y1>l) l=V[i].y2-V[i].y1;
    }
    if(c==1)
    {
        l++;
        fprintf(g,"%d ",l*l);
        int nr=0;
        for(int i=1;i<=K;i++)
            if(V[i].x2-V[i].x1<=l-3&&V[i].y2-V[i].y1<=l-3)
                nr++;
        fprintf(g,"%d",nr);
    }
    else
    {
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=M;j++)
            {
                C[i][j]+=C[i-1][j]+C[i][j-1]-C[i-1][j-1];
                if(C[i][j]) A[i]=1,B[j]=1;
            }
        }
        for(int i=1;i<=N;i++)
        {
            while(i<N&&(!A[i])&&(!A[i+1]))i++;
            for(int j=1;j<=M;j++)
            {
                while(j<M&&(!B[j])&&(!B[j+1])) j++;
                fprintf(g,"%d ",C[i][j]);
            }
            fputc('\n',g);
        }
    }
    return 0;
}
