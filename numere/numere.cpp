#include<fstream>
using namespace std;
ifstream f("numere.in");
ofstream g("numere.out");
int main()
{
    int a,b,maxa=0,maxb=0,uc,c,d,ud;
    f>>a;
    f>>b;
    c=a;
    d=b;
    while(a!=0)
    {
        uc=a%10;
        a=a/10;
        if(maxa<uc)
         {maxa=uc;}
    }
    while(b!=0)
    {
        ud=b%10;
        b=b/10;
        if(maxb<ud)
         maxb=ud;
    }
    if(maxa<maxb)
        {g<<d;}
    else if(maxa==maxb)
        {g<<c<<" "<<d;}
    else if(maxa>maxb)
        {g<<c;}
    f.close();g.close();
    return 0;
}
