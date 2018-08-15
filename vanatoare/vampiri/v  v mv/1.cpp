#include<fstream>
#include<iostream>
using namespace std;
ifstream f("magic.in");
ofstream g("magic.out");
int main()
{
    char m,k,v[1000],maxi;
    int n,i=1,j=1;
    f>>n;
    i=1;
    while(i<=n)
    {
        f>>m;
        if (m>=65)
            {
                k=m-32;
                    g<<k;
            }
            else
            {
               v[j]=m;
               j++;
            }
            i++;
    }
    for(i=1;i<=n;i++)
{
    for(j=1;j<=n;j++)
    {
    if(v[i]<v[j]&&v[i]!=v[j])
    {
        maxi=v[j];
        v[j]=v[i];
        v[i]=maxi;
    }
    }
}
for(i=1;i<=n;i++)
{
cout<<v[i];
}
    g.close();f.close();
    return 0;
}
