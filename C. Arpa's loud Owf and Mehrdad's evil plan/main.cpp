#include <iostream>
#include <bitset>
using namespace std;
int rez=1,T[105],N,val;
bitset <105> viz;
int dfs(int nod)
{
    viz[nod]=1;
    int l=0;
    if(!viz[T[nod]])
        l=dfs(T[nod]);
    return l+1;
}
int gcd(int a,int b)
{
    if(!b)
        return a;
    return gcd(b,a%b);
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>val;
        viz[val]=1;
        T[i]=val;
    }
    for(int i=1;i<=N;i++)
    {
        if(!viz[i])
        {
            cout<<-1;
            return 0;
        }
    }
    viz.reset();
    for(int i=1;i<=N;i++)
    {
        if(!viz[i])
        {
            int aux=dfs(i);
            if(aux%2==0)
                aux/=2;
            rez=rez*aux/gcd(aux,rez);
        }
    }
    cout<<rez;
    return 0;
}
