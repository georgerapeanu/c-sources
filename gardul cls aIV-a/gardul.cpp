#include<fstream>
using namespace std;
ifstream f("gardul.in");
ofstream g("gardul.out");
int main()
{
    long n,p,q,i,l=1,ne=0,r=0,a=0,vi=0;
    f>>n>>p>>q;
    long v[n];
    for(i=0;i<n;i++)
    {
        if(i==l*p-1)
        {
           v[i]=1;
           l++;
        }
        else
            v[i]=0;
    }
    l=1;
    for(i=0;i<n;i++)
    {
        if(i==l*q-1)
        {
            if(v[i]==1)
                v[i]=3;
            else
                v[i]=2;
            l++;
        }
    }
    for(i=0;i<n;i++)
    {
        switch(v[i])
        {
            case 0:ne++;
            break;
            case 1:r++;
            break;
            case 2:a++;
            break;
            case 3:vi++;
            break;
        }
    }
    g<<ne<<"\n"<<r<<"\n"<<a<<"\n"<<vi;
    f.close();g.close();
    return 0;
}
