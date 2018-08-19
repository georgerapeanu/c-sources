#include <iostream>
#include <fstream>
using namespace std;
ifstream f("patrat1.in");
ofstream g("patrat1.out");
const int valmax=1001;
int a[210][210],m,n,ss=0,cp=0,lmax=1;
int dx[]={0,-1,-1,-1,0,1,1,1};
int dy[]={1,1,0,-1,-1,-1,0,1};
void citire()
{
     int i,j;
     f>>m>>n;
     for(i=1;i<=m;i++)
     for(j=1;j<=n;j++)
     f>>a[i][j];

}
void afisare()
{
     int i,j;

     for(i=1;i<=m;i++)
     {
     for(j=1;j<=n;j++)
     g<<a[i][j]<<' ';
     g<<endl;
     }

}
void stralucire()
{
     int i,j,p,k;
     for(i=1;i<=m;i++)
     for(j=1;j<=n;j++)
     {   p=0;
         for(k=0;k<8;k++)
         p=p+(a[i][j]>a[i+dx[k]][j+dy[k]]);

     if(p==8)a[i][j]=valmax,ss++;
     }
}

void constelatie()
{
     int i,j,k;
     for(i=1;i<=m;i++)
     for(j=1;j<=n;j++)
     if(a[i][j]==valmax)
     {
         for(k=1;k<=n-j&&k<=m-i;k++)
         if((a[i][j+k]==valmax)&&(a[i+k][j]==valmax)&&(a[i+k][j+k]==valmax))
         {cp++;
         if(k+1>lmax)lmax=k+1;
         }
     }
}

int main()
{
    citire();
    stralucire();
//    afisare();
    constelatie();
    g<<ss<<'\n';
   g<<cp<<'\n';
      g<<lmax<<'\n';
          return 0;
}

/*#include <fstream>
using namespace std;
ifstream f("patrat1.in");
ofstream g("patrat1.out");
int n,m,v[202][202],k,i,j,l[200][200],nr,maxim,nrcon;
int main()
{
    f>>n>>m;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            f>>v[i][j];
        }
    }
     for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
          if(v[i][j]>v[i][j+1]&&v[i][j]>v[i+1][j]&&v[i][j]>v[i-1][j]&&v[i][j]>v[i][j-1]&&v[i][j]>v[i+1][j+1]&&v[i][j]>v[i-1][j+1]&&v[i][j]>v[i+1][j-1]&&v[i][j]>v[i-1][j-1])
          {
              l[i][j]=1;nr++;
          }
        }
    }
        for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            if(l[i][j]==1)
            {
                 j++;k=1;
                 while(l[i][j]!=0)
                 {
                     if(j<n)
                        j++;
                     else
                        {k=0;break;}
                     k++;
                 }
                 l[i][j]=0;
            }
            j-=k+1;
            if(k!=0)
            {
                if(k>maxim)
                    maxim=k;
                nrcon++;
            }
        }
    }
    g<<nr<<"\n"<<nrcon<<"\n"<<maxim;
    f.close();g.close();
    return 0;
}
*/
