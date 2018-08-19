#include <fstream>
#include <math.h>
using namespace std;
ifstream f("drepteprime.in");
ofstream g("drepteprime.out");
long n,m[19][19],nrrez,ciur[524288],i,j,maxi,nr,nrrez2,k,ni,nj;
int transformare(long baza)
{
     long uc,nrp2=1,rez=0;
    while(baza!=0)
    {
        uc=baza%10;
        baza=baza/10;
        if(uc==1)
        rez=rez+nrp2;
        nrp2=nrp2*2;
    }
    return rez;
}
int main()
{
    f>>n;
    for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    f>>m[i][j];
    maxi=pow(2,n+1);
    ciur[0]=ciur[1]=1;
    for(i=2;i<maxi;i++)
    {
         if(ciur[i]==0)
         {
             for(j=i+i;j<=maxi;j+=i)
             ciur[j]=1;
         }
    }
    //linii si coloane
    for(i=0;i<n;i++)
    {
        nrrez=0;
        nrrez2=0;
        for(j=0;j<n;j++)
        {
            nrrez=nrrez*10+m[i][j];
            nrrez2=nrrez2*10+m[j][i];
        }
        if(ciur[transformare(nrrez)]==0)
        nr++;
        if(ciur[transformare(nrrez2)]==0)
        nr++;
    }
    //diagonala principala
    ni=i=0;nj=j=0;
    for(k=1;k<=n;k++)
    {
        nrrez=0;nrrez2=0;nj=0;
        for(ni=i;ni<n;ni++)
        {
            nrrez=nrrez*10+m[ni][nj];
            if(i!=0)
            nrrez2=nrrez2*10+m[nj][ni];
            nj++;
        }
        if(ciur[transformare(nrrez)]==0)
        nr++;
        if(ciur[transformare(nrrez2)]==0)
        nr++;
       i++;
    }
    //diagonala secundara
    i=0;
    for(k=1;k<=n;k++)
    {
       nj=n-1;nrrez=0;nrrez2=0;
       for(ni=i;ni<n;ni++)
       {
          nrrez=nrrez*10+m[ni][nj];
          if(i!=0)
          nrrez2=nrrez2*10+m[n-nj-1][n-ni-1];
          nj--;
       }
        if(ciur[transformare(nrrez)]==0)
        nr++;
        if(ciur[transformare(nrrez2)]==0)
        nr++;
       i++;
    }
    g<<nr;
    f.close();g.close();
    return 0;
}
