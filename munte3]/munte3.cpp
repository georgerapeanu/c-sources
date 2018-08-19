#include <fstream>
#include <iostream>
using namespace std;
ifstream f("munte3.in");
ofstream g("munte3.out");
long long int n,i,j,nrscv,l,fnrscv;
int v[101];
void munte()
{
        fnrscv=nrscv;
    for(i=2;i<n;i++)
    {
        if(v[i]>v[i-1]&&v[i]>v[i+1])
        {
            nrscv++;
            for(j=i;j<n;j++)
            {
                v[j]=v[j+1];
            }
            n--;
        }
    }
    if(l==0)  {l=1;g<<nrscv<<"\n";}
    if(fnrscv!=nrscv)
    {munte();}
}
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>v[i];
    }
    munte();g<<nrscv<<"\n";g<<n;//cout<<v[1]<<" "<<v[2]<<" "<<v[3]<<" "<<v[4];
    f.close();g.close();
    return 0;
}
