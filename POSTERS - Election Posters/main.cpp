#include <iostream>
#include <cstring>
#include <set>
#include <map>
#define NMAX 80000
using namespace std;
int AINT[4*NMAX+5];
map<int,int> S;
set<int> R;
pair<int,int> Q[NMAX+5];
int T,N;
void propag(int nod)
{
    if(!AINT[nod])return ;
    AINT[2*nod]=AINT[nod];
    AINT[2*nod+1]=AINT[nod];
    AINT[nod]=0;
}
void init()
{
    memset(AINT,0,sizeof(AINT));
}
void u(int nod,int st,int dr,int S,int D,int val)
{
    if(dr<S||st>D)return ;
    if(S<=st&&dr<=D)
    {
        AINT[nod]=val;
        return;
    }
    propag(nod);
    int mid=(st+dr)/2;
    u(nod*2,st,mid,S,D,val);
    u(nod*2+1,mid+1,dr,S,D,val);
}
void baga(int nod,int st,int dr)
{
    if(st==dr)
    {
        R.insert(AINT[nod]);
        return ;
    }
    int mid=(st+dr)/2;
    propag(nod);
    baga(nod*2,st,mid);
    baga(nod*2+1,mid+1,dr);
}
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>N;
        init();
        S.clear();
        R.clear();
        R.insert(0);
        for(int i=1;i<=N;i++)
        {
            cin>>Q[i].first>>Q[i].second;;
            S[Q[i].first]=1;
            S[Q[i].second]=1;
        }
        int nr=1;
        for(auto &it:S)it.second=nr++;
        for(int i=1;i<=N;i++)
        {
            u(1,1,S.size(),S[Q[i].first],S[Q[i].second],i);
        }
        baga(1,1,S.size());
        cout<<R.size()-1<<"\n";
    }
    return 0;
}
