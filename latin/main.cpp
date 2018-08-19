#include <fstream>
using namespace std;
ifstream f("latin.in");
ofstream g("latin.out");
int n,i,j,l,k,m[501][501],nrp,r[501],c[501],kl,s,mkl,mk,minkl,mink,gasit,nr,nm,ia[501],ja[501],la[501];
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
        f>>m[i][j];
        }
    }
   for(i=1;i<=n;i++)
   {
       l=1;nm=1;
       for(j=1;j<=n;j++)
       {
           gasit=0;
           l=m[i][j];
           for(k=i;k<=i+l;k++)
           {
               for(kl=j;kl<=j+l;kl++)
               {
                   r[k]+=m[k][kl];
                   c[kl]+=m[k][kl];
                   mkl=kl;
               }
               mk=k;
               minkl=j;
           }
           mink=i;
           s=l*(l+1)/2;
            for(k=mink;k<=mk;k++)
           {
              if(k==mink)
              {
                  if(r[k]!=c[k])
                    {
                        gasit=1;
                        break;
                    }
              }
              else
              {
                  if((r[k]!=c[k])||(r[k]!=c[k-1])||(c[k]!=c[k-1]))
                   {
                    gasit=1;
                    break;
                   }
              }
              if(k==mk)
                if(s!=r[k])
              {
                  gasit=1;
                  break;
              }
           }
           if(gasit==0)
           {
               nr++;
               ia[nm]=i;
               ja[nm]=j;
               la[nm]=l;
               nm++;
           }
           if(j+l>=n)
                break;
            for(k=i;k<=i+l;k++)
           {
               for(kl=j;kl<=j+l;kl++)
               {
                   r[k]=0;
                   c[kl]=0;
               }
           }
            l++;
       }
   }
   g<<nr<<"\n";
   for(i=1;i<=nr;i++)
   {
       g<<ia[i]<<" "<<ja[i]<<" "<<la[l]<<"\n";
   }
    return 0;
}
