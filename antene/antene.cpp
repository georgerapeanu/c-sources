#include<fstream>
using namespace std;
ifstream f("antene.in");
ofstream g("antene.out");
int main()
{
    int i,a,b,c,n,maxi=0,mini,k=0,gasit=0,l=1,r[l];
    f>>a>>b>>n;
    int v[n];
    for(i=0;i<n;i++)
    {
        f>>v[i];

    }
    r[l-1]=0;
    l++;
    for(i=0;i<n;i++)
    {
        if(i==1)
        {

            if(v[i]>a&&v[i]>v[i+1])
            {

                g<<(i+1)<<" ";
                gasit=1;
                r[l-1]=i+1;
                l++;
            }
        }
        else if(i==n-1)
        {
             if(v[i]>b&&v[i]>v[i-1])
             {
             g<<(i+1)<<" ";
             gasit=1;
             r[l-1]=i+1;
             l++;
             }

        }
        else
        {
            if(v[i]>v[i-1]&&v[i]>v[i+1])
            {
               g<<(i+1)<<" ";gasit=1;
               r[l-1]=i+1;l++;
            }
        }
    }
    r[l-1]=n+1;
    if(gasit==0)
    {
    g<<0<<"\n"<<(n+1)<<"\n"<<(n+1);
    }
    else
    {
    g<<"\n";
    l=l-1;
    for(i=1;i<=l;i++)
    {
        if(i==1)
        {
            mini=r[1]-r[0];
        }
        if(r[i]-r[i-1]<mini)   mini=r[i]-r[i-1];
        if(r[i]-r[i-1]>maxi)   maxi=r[i]-r[i-1];
    }
    g<<maxi<<"\n"<<mini;
    }
    f.close();g.close();
    return 0;
}

