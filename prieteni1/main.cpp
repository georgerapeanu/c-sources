#include <fstream>
#include <iostream>
using namespace std;
ifstream f("prieteni1.in");
ofstream g("prieteni1.out");
long long n,v[101],s[101],ciur[65536],nr[65536],i,c,uc,j,afis[1000],l;
int euclid(long long a, long long b)
{
    if(b==0)
    return a;
    else return euclid(b,a%b);
}
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
    f>>v[i];
    nr[v[i]]=1;
    c=v[i];
    while(c!=0)
    {
        uc=c%10;
        s[i]+=uc;
        c=c/10;
    }
    }
    ciur[0]=1;
    for(i=2;i<=65536;i++)
    {
        if(ciur[i]==0)
        for(j=i+i;j<=65536;j+=i)
        {
            ciur[j]=1;
        }
    }
    l=1;
    for(i=1;i<=n;i++)
    {
        if(euclid(v[i],s[i])==1)
        {
             for(j=s[i];j<v[i];j++)
             {
                 if(ciur[j]==0&&nr[j]==0)
                 {afis[l]=j;l++;nr[j]=1;}
             }
        }
        afis[l]=v[i];l++;
    }
    g<<l-1<<"\n";
    for(i=1;i<l;i++)
    g<<afis[i]<<" ";
    f.close();g.close();
    return 0;
}
