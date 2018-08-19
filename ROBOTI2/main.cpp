#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;
ifstream f("roboti.in");
ofstream g("roboti.out");
int i,n,v[10000],st,fn,optst,optfn,medie,suma1,suma2,suma,j,dif=99999;
void permutare()
{
    int hold=v[0];
    for(int i1=0;i1<n-1;i1++)
    v[i1]=v[i1+1];
    v[n-1]=hold;
}
int main()
{
    f>>n;
    for(i=0;i<n;i++)
    {f>>v[i];medie+=v[i];}
    suma=medie;
    medie/=2;
    for(i=0;i<n;i++)
    {
        st=i+1;
        suma1=suma2=0;
        j=0;
        while(suma1+v[j]<=medie)
        suma1+=v[j++];
        fn=j+1+i;
        suma2=suma-suma1;
        if(abs(medie-suma1)<dif)
        {
            dif=abs(medie-suma1);
            optst=st;
            optfn=fn;
        }
        permutare();
    }
    g<<optst<<" "<<optfn;
    return 0;
}
