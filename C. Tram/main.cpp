#include <iostream>
#include <algorithm>
using namespace std;
int s,x1,x2,t1,t2,p,d,sens;
int t,x;
int main()
{
    cin>>s>>x1>>x2>>t1>>t2>>p>>d;
    while(p!=x1)
    {
        if(p==s&&d==1)
            d=-1;
        if(p==0&&d==-1)
            d=1;
        p+=d;
        t+=t1;
    }
    while(p!=x2)
    {
        if(p==s&&d==1)
            d=-1;
        if(p==0&&d==-1)
            d=1;
        p+=d;
        t+=t1;
    }
    cout<<min(t,t2*abs(x1-x2));
    return 0;
}
///daca alege sa ia tranvaiul,se va afla undeva intre x1 si x2.tranvaiul va ajunge dupa acelasi timp la x2,indiferent ca se urca sau nu
///asadar e ok sa stea in x1 pana cand vine tranvaiul.
///daca nu il ia rez=t2*abs(x1-x2)
