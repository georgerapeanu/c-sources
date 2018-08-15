#include <iostream>
#include <algorithm>
#define l second
#define p first
using namespace std;
pair<long long,long long> V[100005];
long long st,dr;
long long N;
long long nr;
int main()
{
    cin>>N;
    for(long long i=1;i<=N;i++)
    {
        cin>>V[i].l>>V[i].p;
    }
    sort(V+1,V+1+N);
    st=dr=-1000000000;
    for(long long i=1;i<=N;i++)
    {
        if(dr<=V[i].p)
        {
            long long newst,newdr;
            newst=dr;
            newdr=max(V[i].p,newst+V[i].l);
            st=newst;
            dr=newdr;
            nr++;
        }
        else if(V[i].l<dr-st)
        {
            long long newst,newdr;
            newst=st;
            newdr=max(V[i].p,st+V[i].l);
            st=newst;
            dr=newdr;
        }
    }
    cout<<nr;
    return 0;
}
