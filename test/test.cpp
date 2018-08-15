#include<iostream>
#include<fstream>
using namespace std;
ifstream f("test.in");
ofstream g("test.out");
long v[14];
int main()
{
    long a,b,z,maxim=0,i,l=1,ucb,n,m,o,e=1,pca,p=1,k;
    f>>a>>b;
    z=b;
    o=a;
    k=a;
    while(z>9)
    {
        l=l*10;
        z=z/10;
    }
     while(o>9)
    {
        e=e*10;
        o=o/10;
        p++;
    }
    ucb=b%10;
    for(i=1;i<=p;i++)
    {
        pca=a/e;
        n=b-ucb+pca;
        m=b%l+pca*l;
        a=a%e;
        e=e/10;
        v[i-1]=m;
        v[i+p-1]=n;

    }
    v[2*p]=k;
    v[2*p+1]=b;
    for(i=0;i<=2*p+1;i++)
    {
        cout<<v[i]<<" ";
        if(v[i]>maxim)
            maxim=v[i];
    }
    g<<maxim;
    f.close();g.close();
    return 0;
}
