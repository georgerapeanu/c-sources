#include <fstream>
#include <cmath>
using namespace std;
ifstream f("input.in");
ofstream g("output.out");
void arc()
{
    int d=0,dirl[]={-1,0,1,0},dirc[]={0,1,0,-1},n,nr=2,div,i,j,m[150][150];
    f>>n;
    bool ciur[150]={false};
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    m[i][j]=0;
    ciur[0]=ciur[1]=1;
    for(i=2;i<=n*n;i++)
    {
        if(ciur[i]==0)
        {
            for(j=i+i;j<=n*n;j+=i)
            ciur[j]=1;
        }
    }
    for(i=0;i<=n+1;i++)
    m[i][0]=m[i][n+1]=m[0][i]=m[n+1][i]=-1;
   i=j=1;
   while(m[i+dirl[d]][j+dirc[d]]==0||m[i+dirl[(d+1)%4]][j+dirc[(d+1)%4]]==0)
   {
       m[i][j]=nr;
       if(m[i+dirl[d]][j+dirc[d]]!=0)
       d=(d+1)%4;
       i+=dirl[d];
       j+=dirc[d];
       if(m[i+dirl[d]][j+dirc[d]]!=0&&m[i+dirl[(d+1)%4]][j+dirc[(d+1)%4]]!=0)
       break;
       if(ciur[nr]==1)
       {
           div=ceil(double(nr)/2);
           while(nr%div!=0)
           div--;
           m[i][j]=div;
           i+=dirl[d];
       j+=dirc[d];
       }
       nr++;
   }
   i=j=n/2;
   if(n%2==1)
   {
       i=j=n/2+1;
   }
   m[i][j]=nr;
   for(i=1;i<=n;i++)
   {
       for(j=1;j<=n;j++)
       g<<m[i][j]<<" ";
       g<<"\n";
   }
}
int main()
{
    arc();
    return 0;
}
