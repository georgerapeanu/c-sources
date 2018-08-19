#include <fstream>
using namespace std;
ifstream f("tetris.in");
ofstream g("tetris.out");
int m1[1001][1001],m,n,v[1001];
void umplere(int i,int l,int j)
{
    int i1,j1;
   for(i1=i;i1>=i-l+1;i1--)
    for(j1=j;j1<j+l;j1++)
    {m1[i1][j1]=1;}
    for(j1=j;j1<j+l;j1++)
    v[j1]=n-(i-l+1)+1;
}
int main()
{
    int a,b,i=0,maxim,j,nrmax=1,nr=0;
    f>>n>>m;
    while(f>>a>>b)
    {
        maxim=0;
       for(j=b;j<=a+b-1;j++)
       {
           maxim=(maxim>v[j] ? maxim:v[j]);
       }
       maxim++;
       if((n-maxim+1)-a+1>0&&a+b-1<=m)
       umplere(n-maxim+1,a,b);
       else
       break;
    }
    maxim=0;
     for(i=1;i<=m;i++)
     {
         nr=1;
         while(v[i]==maxim)
         {
             nr++;i++;
         }
         if(nr>nrmax)
         nrmax=nr;
         if(maxim<v[i])
         {
             maxim=v[i];nrmax=1;
         }
     }
     g<<maxim<<"\n"<<nrmax;
    return 0;
}
