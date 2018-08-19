#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("startrek.in","r");
FILE *g=fopen("startrek.out","w");
int N,P,Q,M;
int frecv[100005];
int G[100005];
char C[100005];
int ind=1,lan;
void u(int poz,int val)
{
    for(int i=poz;i<=N;i+=(i&(-i)))
        frecv[i]+=val;
}
int q(int poz)
{
    int rez=0;
    for(int i=poz;i;i-=(i&(-i)))
        rez+=frecv[i];
    return rez;
}
int main()
{
    fscanf(f,"%d%d%d%d",&N,&M,&P,&Q);
    for(int i=1;i<=M;i++)
    {
        int s,t;
        fscanf(f,"%d %d",&s,&t);
        G[s]=t;
    }
    int an=1;
    for(int i=1;i<=N;i++)
    {
        if(q(an)-q(an-1)==P)
        {
            an++;
        }
        u(an,1);
        if(G[i]&&G[i]!=an)
        {
            while(q(an)<=i)
            {
                u(lan,min(Q-frecv[lan],i-q(an)));
                if(frecv[lan]==Q)
                    lan++;
            }
        }
    }
    fprintf(g,"%d\n",an);
    for(int i=1;i<=an;i++)
        for(int j=q(i)-q(i-1);j;j--)
            fprintf(g,"%d ",i);
    fclose(f);
    fclose(g);
    return 0;
}
