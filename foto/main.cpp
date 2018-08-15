#include <fstream>
#include <iostream>
using namespace std;
ifstream f("foto.in");
ofstream g("foto.out");
long v[10000],m[100][100],i,j,p,a,b,k,nrmax;
int fil(int x,int y)
{
    if(m[x][y]==0)
    {
        m[x][y]=2;p++;
        if(y+1<b)
        fil(x,y+1);
        if(x+1<a)
        fil(x+1,y);
        if(y>0)
        fil(x,y-1);
        if(x>0)
        fil(x-1,y);
    }
}
int main()
{
    f>>a>>b;
    for(i=0;i<a;i++)
        for(j=0;j<b;j++)
          f>>m[i][j];
    for(i=0;i<a;i++)
        for(j=0;j<b;j++)
          {
              p=0;
              fil(i,j);
              v[k]=p;
              k++;
          }
        for(i=0;i<k;i++)
        {
            if(v[i]>nrmax)
                nrmax=v[i];
        }
        g<<nrmax;
    return 0;
}
