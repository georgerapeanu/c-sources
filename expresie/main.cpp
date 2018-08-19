#include <fstream>
using namespace std;
ifstream f("expresie.in");
ofstream g("expresie.out");
long long int a,b,v[10001],i,n,maxim,suma,j,suma2;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>v[i];maxim+=v[i];
    }
    suma2=suma=maxim;
    for(i=1;i<n-1;i++)
    {
        suma=suma2;
        suma=suma-v[i]-v[i+1]-v[i+2]+v[i]*v[i+1]*v[i+2];
        if(suma>maxim)
        {
            maxim=suma;
        }
    }
    for(i=1;i<n;i++)
    {
        for(j=i+2;j<n;j++)
        {
            suma=suma2;
            suma=suma-v[i]-v[i+1]-v[j]-v[j+1]+v[i]*v[i+1]+v[j]*v[j+1];
            if(suma>maxim)
                maxim=suma;
        }
    }
    g<<maxim;
    f.close();g.close();
    return 0;
}
