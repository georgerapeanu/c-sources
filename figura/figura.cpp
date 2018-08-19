#include<fstream>
#include<iostream>
using namespace std;
ifstream f("figura.in");
ofstream g("figura.out");
int i,j,d,n,m[22][22],v[2][400],nr,a,b;
int main()
{
    f>>d>>n;
    nr=4*n;
    for(i=0;i<n;i++)
    {
        f>>a>>b;
        v[0][i]=a;
        v[1][i]=b;
        m[a][b]=1;
    }
    for(i=0;i<n;i++)
    {
        a=v[0][i];
        b=v[1][i];
        if(m[a][b-1]==1)
            nr--;
        if(m[a][b+1]==1)
           nr--;
        if(m[a-1][b]==1)
        nr--;
        if(m[a+1][b]==1)
            nr--;
    }
    g<<nr;
   f.close();
   g.close();
   return 0;
}
