#include <iostream>
using namespace std;
string a;
int fr[1000005];
int F[1000005];
long long rez=0;
int u(int nod)
{
    if(fr[nod]>=3)return nod;
    fr[nod]++;int rez=u(F[nod]);
    if(fr[nod]>=3)return nod;
    return rez;
}
int main()
{
    cin>>a;
    a=" "+a;
    for(int i=2;i<a.size();i++)
    {
        int k=F[i-1];
        while(k&&a[k+1]!=a[i])k=F[k];
        if(a[k+1]==a[i])k++;
        F[i]=k;
    }
    fr[0]=2;
    for(int i=1;i<a.size();i++)
    {
        rez+=u(i);
    }
    cout<<rez;
    return 0;
}
