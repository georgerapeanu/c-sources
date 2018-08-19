#include <fstream>
#include <iostream>
#include<cstring>
using namespace std;
ifstream f("criptmat.in");
ofstream g("criptmat.out");
char c[200],k[200],m[200][200];
int n,i,j,l;
int main()
{
     f>>n;
     f>>c;
     for(i=0;i<strlen(c)/n;i++)
     {
         for(j=0;j<n;j++)
         {
             if(i%2==0)
             {
                 m[i][j]=c[i*n+j];
             }
             else
                m[i][j]=c[i*n+n-j-1];
         }
     }
     for(j=0;j<n;j++)
         {
             for(i=0;i<strlen(c)/n;i++)
             {
                 k[l]=m[i][j];
                 l++;
             }
         }

         g<<k;
    f.close();g.close();
    return 0;
}
