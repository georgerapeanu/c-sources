#include <cstdio>
#include <bitset>
#include <queue>
#define t first
#define nod1 second.first
#define nod2 second.second
using namespace std;
int N,L;
int D[500005];
int nxt[500005];
double S[500005];
bitset<500005> B;
priority_queue<pair<double,pair<int,int> >,vector<pair<double,pair<int,int> > >,greater<pair<double,pair<int,int> > > > H;
int main()
{
    scanf("%d %d",&N,&L);
    for(int i=1;i<=N;i++)
    {
        nxt[i]=i+1;
        scanf("%d %lf",&D[i],&S[i]);
    }
    nxt[N]=1;
    for(int i=1;i<=N;i++)
    {
        if(S[i]>S[nxt[i]])
            H.push({(D[nxt[i]]-D[i]+L*(D[nxt[i]]<D[i]))/(S[i]-S[nxt[i]]),{i,nxt[i]}});
    }
    while(!H.empty())
    {
        pair<double,pair<int,int> > a=H.top();H.pop();
        if(B[a.nod1])continue;
        B[a.nod2]=1;
        printf("%d\n",a.nod2);
        nxt[a.nod1]=nxt[a.nod2];
        int i=a.nod1;
        if(S[i]>S[nxt[i]])
            H.push({(D[nxt[i]]-D[i]+L*(D[nxt[i]]<D[i]))/(S[i]-S[nxt[i]]),{i,nxt[i]}});
    }
    printf("Winner(s): ");
    for(int i=1;i<=N;i++)
        if(!B[i])
            printf("%d%s",i,(i==N ? "":"\n"));
    return 0;
}
