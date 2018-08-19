#include <fstream>
#include <cstring>
using namespace std;
ifstream f("matrix.in");
ofstream g("matrix.out");
char v[200];
long ma[100][100],j,i,n,m,l,temp,temp2;
int main()
{
   f>>n>>m;
   for(i=0;i<n;i++)
   for(j=0;j<m;j++)
   f>>ma[i][j];
   f>>v[0];
   f.getline(v+1,200);
   for(i=0;i<strlen(v);i+=2)
   {
       if(v[i]=='F')
       {
           if(v[i+1]=='H')
           {
               for(j=0;j<n/2;j++)
               {
                   for(l=0;l<m;l++)
                   {
                      temp=ma[j][l];
                      ma[j][l]=ma[n-j-1][l];
                      ma[n-j-1][l]=temp;
                   }
               }
           }
           else
           {
               for(l=0;l<m/2;l++)
               {
                   for(j=0;j<n;j++)
                   {
                          temp=ma[j][l];
                          ma[j][l]=ma[j][m-l-1];
                          ma[j][m-l-1]=temp;
                   }
               }
           }
       }
       else
       {
           if(v[i+1]=='H')
           {
               for(j=0;j<n;j++)
               {
                   temp=ma[j][0];
                   for(l=0;l<m;l++)
                   {
                         if(l+1<m)
                         {
                             temp2=ma[j][l+1];
                             ma[j][l+1]=temp;
                             temp=temp2;
                         }
                         else
                         {
                             ma[j][0]=temp;
                         }
                   }
               }
           }
           else
           {
               for(l=0;l<m;l++)
               {
                   temp=ma[0][l];
                   for(j=0;j<n;j++)
                   {
                       if(j+1<n)
                       {
                           temp2=ma[j+1][l];
                           ma[j+1][l]=temp;
                           temp=temp2;
                       }
                       else
                       {
                           ma[0][l]=temp;
                       }
                   }
               }
           }
       }
   }
   for(i=0;i<n;i++)
   {
   for(j=0;j<m;j++)
   {g<<ma[i][j]<<" ";}
   g<<'\n';
   }
   f.close();g.close();
    return 0;
}
