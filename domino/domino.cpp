#include<fstream>
using namespace std;
ifstream f("domino.in");
ofstream g("domino.out");
int main()
{
    int n,i,k=1,maxim=0,l;
    f>>n;
    int p[n],h[n],a[n];
    for(i=0;i<n;i++)
    {
        f>>p[i]>>h[i];
        a[i]=p[i]+h[i];
    }
    for(i=1;i<n;i++)
    {
        if(a[i-1]<p[i])
            k++;
    }
    g<<k<<" ";
    l=1;
    for(i=1;i<n;i++)
    {
        if(a[i-1]>p[i])
            l++;
        if(l>maxim)
            maxim=l;
        if(a[i-1]<p[i])
            l=1;
    }
    g<<maxim;
    return 0;
}
