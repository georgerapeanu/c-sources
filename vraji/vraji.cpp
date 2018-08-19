#include<fstream>
using namespace std;
ifstream f("vraji.in");
ofstream g("vraji.out");
int main()
{
    int a,b,n,maxdiv,i,maxi=0,j,k;
    f>>n;
    int v[n];
    for(i=0;i<n;i++)
    {
        f>>a>>b;
        v[i]=a*b;
        if(v[i]>maxi)
            maxi=v[i];

    }
    int mini=v[0];
    g<<maxi<<"\n";
    for(i=1;i<=mini;i++)
    {
        k=1;
        for(j=0;j<n;j++)
        {
            if(v[j]%i!=0)
            {
                k=0;j=n;
            }
        }
        if(k==1)
            maxdiv=i;
    }
    g<<maxdiv;
    f.close();g.close();
    return 0;
}
