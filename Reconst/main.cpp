#include <cstdio>
using namespace std;
FILE *f=fopen("reconst.in","r");
FILE *g=fopen("reconst.out","w");
int dr[2005];
int V[2005];
int N,A,B,S,M;
void ins(int a,int b,int s)
{
    if(!dr[a])
    {
        dr[a]=b;
        V[a]=s;
    }
    else if(dr[a]>b)ins(b+1,dr[a],V[a]-s);
    else if(dr[a]<b)ins(dr[a]+1,b,s-V[a]);
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    while(M--)
    {
        fscanf(f,"%d%d%d",&A,&B,&S);
        ins(A,B,S);
    }
    for(int i=N;i;i--)
        for(int j=i+1;j<=dr[i];j++)
            V[i]-=V[j];
    for(int i=1;i<=N;i++)fprintf(g,"%d ",V[i]);
    fclose(f);
    fclose(g);
    return 0;
}
