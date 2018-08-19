#include<fstream>
using namespace std;
ifstream f("bete.in");
ofstream g("bete.out");
int main()
{
    int n,a,b,s=0,i,maxa=0,maxb=0,l=1,h=1,max;
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        s=s+a;
        if(a==maxa)
            l++;
        if(a>maxa)
        {
            l=1;
            maxa=a;
        }
    }
    for(i=1;i<=n;i++)
    {
        f>>b;
        s=s+b;
        if(b==maxb)
            h++;
        if(maxb<b)
        {
            maxb=b;
            h=1;
        }
    }
    s=s/n;
    max=maxa+maxb;
    g<<s<<"\n";
    g<<max<<"\n";
    if(l==h)
        g<<l;
    if(l<h)
        g<<l;
    if(l>h)
        g<<h;
    f.close();g.close();
    return 0;
}
