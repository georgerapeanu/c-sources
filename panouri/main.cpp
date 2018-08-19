#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("panouri.in");
ofstream g("panouri.out");
int N,T,i,j,nrs,frecv[200010],V[2000010],L=20000010,val;
bool t[200010];
int main()
{
    f>>N>>T;
    for(i=1;i<=N;i++)
        f>>V[i];
    for(i=1;i<=T;i++)
        {f>>val;t[val]=1;}

    i=j=1;
    frecv[V[i]]=1;
    if(frecv[V[j]]-1==0&&frecv[V[j]]==t[V[j]])
                nrs++;
    while(j<=N)
    {
        if(nrs==T)
        {
            L=min(L,j-i);
            frecv[V[i]]--;
            if(frecv[V[i]]<t[V[i]])
                nrs--;
            i++;
        }
        else
        {
            j++;
            frecv[V[j]]++;
            if(frecv[V[j]]-1==0&&frecv[V[j]]==t[V[j]])
                nrs++;
        }
    }
    g<<L;
    f.close();
    g.close();
    return 0;
}
