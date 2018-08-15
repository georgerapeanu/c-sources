#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int N,Q;
vector<int> AINT[120005];
void build(int nod,int st,int dr)
{
    if(st==dr)
    {
        int val;
        scanf("%d",&val);
        AINT[nod].push_back(val);
        return ;
    }
    build(nod*2,st,(st+dr)/2);
    build(nod*2+1,(st+dr)/2+1,dr);
    AINT[nod].resize(AINT[2*nod].size()+AINT[2*nod+1].size());
    merge(AINT[nod*2].begin(),AINT[nod*2].end(),AINT[nod*2+1].begin(),AINT[nod*2+1].end(),AINT[nod].begin());
}
int q(int nod,int st,int dr,int i,int j,int k)
{
    if(dr<i||st>j)
        return 0;
    if(i<=st&&dr<=j)
    {
        return AINT[nod].end()-lower_bound(AINT[nod].begin(),AINT[nod].end(),k+1);
    }
    return q(nod*2,st,(st+dr)/2,i,j,k)+q(nod*2+1,(st+dr)/2+1,dr,i,j,k);
}
int main()
{
    scanf("%d",&N);
    build(1,1,N);
    scanf("%d",&Q);
    int ans=0;
    while(Q--)
    {
        int i,j,k;
        scanf("%d%d%d",&i,&j,&k);
        i^=ans;
        j^=ans;
        k^=ans;
        if(i<1)i=1;
        if(j>N)j=N;
        if(i>j)ans=0;
        else
        ans=q(1,1,N,i,j,k);
        printf("%d\n",ans);
    }
    return 0;
}
