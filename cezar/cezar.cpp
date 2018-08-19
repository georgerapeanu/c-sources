#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("cezar.in","r");
FILE *g=fopen("cezar.out","w");
int N,K;
int cost;
priority_queue<pair<int,int> > H;
int W[10005];
int D[10005];
int S[10005];
int main()
{
    fscanf(f,"%d %d\n",&N,&K);
    for(int i=1;i<N;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        D[x]^=y;S[x]++;
        D[y]^=x;S[y]++;
    }
    for(int i=1;i<=N;i++)
    {
        W[i]=1;
        if(S[i]==1)
        {
            H.push({-W[i],i});
        }
    }
    while(N>K+1)
    {
        cost-=H.top().first;
        int nod=H.top().second;
        H.pop();
        W[D[nod]]+=W[nod];
        D[D[nod]]^=nod;S[D[nod]]--;
        if(S[D[nod]]==1)
        {
            H.push({-W[D[nod]],D[nod]});
        }
        N--;
    }
    fprintf(g,"%d",cost);
    fclose(f);
    fclose(g);
     return 0;
}
