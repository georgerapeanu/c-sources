#include<fstream>
using namespace std;
ifstream f("bete1.in");
ofstream g("bete1.out");
int main()
{
    int n,i,c,s=0,maxa=0,nrmaxa=0,maxb=0,nrmaxb=0,maxi,nrmax;
    f>>n;
    int a[n],b[n];
    for(i=0;i<2*n;i++)
    {
        f>>c;
        if(i<n)
        a[i]=c;
        else
            b[i-n]=c;
        s+=c;
    }
    s=s/n;
    g<<s<<"\n";
    for(i=0;i<n;i++)
    {
        if(a[i]>maxa)
            maxa=a[i];
        if(b[i]>maxb)
            maxb=b[i];
    }
    maxi=maxa+maxb;
    g<<maxi<<"\n";
    for(i=0;i<n;i++)
    {
        if(a[i]==maxa)
            nrmaxa++;
        if(b[i]==maxb)
            nrmaxb++;
    }
    nrmax=min(nrmaxa,nrmaxb);
    g<<nrmax;
    f.close();g.close();
    return 0;
}
