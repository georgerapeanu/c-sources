#include <iostream>
#include <vector>
#include <bitset>
using namespace std;
long long d[5005][5005];
vector<pair<int,int> > V[5005];
int N,x,y,z;
long long s;
int urm[5005],nrnod[5005];
bitset<5005> activ;
void btr(int pas,int suma)
{
    if(pas>N)
    {
        s+=suma;
    }
    else
    {
        for(int i=urm[0],prev=0;i;prev=i,i=urm[i])
        {
            long long tmp=0;
            for(auto it:V[i])
                tmp+=d[i][it.first]*(!activ[it.first]);
            activ[i]=1;
            urm[prev]=urm[i];
            btr(pas+1,suma+tmp);
            urm[prev]=i;
            activ[i]=0;
        }
    }
}
long long dfs(int nod,int tata)
{
    for(auto it:V[nod])
    {
        if(it.first!=tata)
        {
            dfs(it.first,nod);
            d[nod][it.first]=0;
            for(int i=1;i<=N;i++)
                d[nod][it.first]+=d[it.first][i]*(i!=nod);
            d[nod][it.first]+=nrnod[it.first]*it.second;
            nrnod[nod]+=nrnod[it.first];
        }
    }
}
int main()
{
    cin>>N;urm[0]=1;
    for(int i=1;i<N;i++)
    {
        urm[i]=i+1;
        cin>>x>>y>>z;
        V[x].push_back(make_pair(y,z));
        V[y].push_back(make_pair(x,z));
    }
    for(int i=1;i<=N;i++)
    {
        for(int i=1;i<=N;i++)
            nrnod[i]=1;
        dfs(i,0);
    }
    btr(1,0);
    cout<<s;
    return 0;
}
