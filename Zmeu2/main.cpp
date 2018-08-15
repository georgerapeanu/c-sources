#include <cstdio>
#include <queue>
#include <unordered_set>
#define nod first
#define cap second.first
#define cost second.second
using namespace std;
FILE *f=fopen("zmeu2.in","r");
FILE *g=fopen("zmeu2.out","w");
bool B[201][201];
short C[201];
short c[201];
short d[201],nxt[201][201];
short N,P,K,x,y,rez;
priority_queue <pair<int,pair<int,int> > > H;
int main()
{
    fscanf(f,"%hd%hd%hd",&N,&P,&K);
    for(int i=1;i<=P;i++)
        {fscanf(f,"%hd%hd",&d[i],&c[i]);B[i][1]=B[P][i]=B[i][i]=1;C[i]=(1<<14);}
   B[1][P]=B[P][1]=1;
    for(int i=1;i<=K;i++)
    {fscanf(f,"%hd%hd",&x,&y);B[x][y]=1;}
    for(int i=1;i<=P;i++)
    {
        int prev=0;
        for(int j=1;j<=P;j++)
        {
            if(!B[i][j])
            {
                nxt[i][prev]=j;
                prev=j;
            }
        }
    }
    if(N-c[1]<=0)
    {
        fprintf(g,"-1");return 0;
    }
    H.push(make_pair(1,make_pair(N-c[1],d[1])));
    C[1]=d[1];
    while(!H.empty())
    {
        pair<int,pair<int,int> >p=H.top();
        H.pop();
        if(p.cost!=C[p.nod])
            continue;
        for(int it=nxt[p.nod][0];it;it=nxt[p.nod][it])
            if(C[it]>p.cost+d[it]&&p.cap>c[it])
            {C[it]=p.cost+d[it];H.push(make_pair(it,make_pair(p.cap-c[it],p.cost+d[it])));}
    }
    fprintf(g,"%d",C[P]);
    fclose(f);
    fclose(g);
    return 0;
}
