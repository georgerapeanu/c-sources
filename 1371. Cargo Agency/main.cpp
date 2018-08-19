#include <iostream>
#include <iomanip>
#include <vector>
#define LL long long
using namespace std;
struct data{LL sumainterna,sumarad,nrnoduri;};
LL N;
vector<pair<LL,LL> >  G[50005];
data dfs(LL nod,LL tata)
{
    vector<data> A;A.clear();
    data rez={0,0,1};
    data a;
    for(auto it:G[nod])
    {
        if(it.first!=tata)
        {
            a=dfs(it.first,nod);A.push_back(a);
            rez.nrnoduri+=a.nrnoduri;
            rez.sumarad+=a.sumarad+a.nrnoduri*it.second;
            rez.sumainterna+=a.sumarad+a.sumainterna;
        }
    }
    int i=0;
    for(auto it:G[nod])
    {
        if(it.first!=tata)
        {
            a=A[i];i++;
            rez.sumainterna+=(a.sumarad+a.nrnoduri*it.second)*(rez.nrnoduri-1-a.nrnoduri);
        }
    }
    return rez;
}
int main()
{
    cin>>N;
    LL a,b,c;
    for(int i=1;i<N;i++)
    {
        cin>>a>>b>>c;
        G[a].push_back(make_pair(b,c));
        G[b].push_back(make_pair(a,c));
    }
    data rez=dfs(1,0);
    cout<<fixed<<setprecision(6)<<2*double(rez.sumainterna+rez.sumarad)/(N*(N-1));
    return 0;
}
