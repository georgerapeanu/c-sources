#include <iostream>
#include <algorithm>
#define y first
#define ind second
#define LL long long
#include <set>
using namespace std;
typedef pair<LL,LL> pii;
set<pii> a,b;
LL N;
typedef struct {LL A,B;} functie;
functie f[100005];
LL x1,x2;
bool ok;
set <pii> ord(LL x)
{
    set <pii> tmp;
    tmp.clear();
    for(int i=1;i<=N;i++)
    {
        tmp.insert(make_pair(f[i].A*x+f[i].B,i));
    }
    return tmp;
}
bool cmp(functie a,functie b)
{
    if(a.A*x1+a.B!=b.A*x1+b.B)
        return a.A*x1+a.B<b.A*x1+b.B;
    return a.A<b.A;
}
int main()
{
    cin>>N;
    cin>>x1>>x2;
    for(int i=1;i<=N;i++)
    {
        cin>>f[i].A>>f[i].B;
    }
    sort(f+1,f+1+N,cmp);
    a=ord(x1);
    b=ord(x2);
    for(set<pii> ::iterator it1=a.begin(),it2=b.begin();it1!=a.end();it1++,it2++)
    {
        ok|=((*it1).second!=(*it2).second);
    }
    cout<<(ok ? "YES":"NO");
    return 0;
}
