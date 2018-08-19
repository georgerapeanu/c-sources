#include <fstream>
#include <math.h>
using namespace std;
ifstream f("2b1.in");
ofstream g("2b1.out");
long long n,a=1,b=2,v[2000],i,flag=1,j,k,temp;
int main()
{
    f>>n;
    for(a=1;a<n;a=a*2)
    {
        for(b=a*2;b<n;b=b*2)
        {
           if(a+b>n)
           break;
           v[i]=a+b;
           i++;
        }
    }
    k=i;
    for(i=1;i<=k&&flag;i++)
     {
          flag=0;
          for(j=0;j<k-1;j++)
         {
               if (v[j+1]<v[j])
              {
                    temp = v[j];
                    v[j] = v[j+1];
                    v[j+1] = temp;
                    flag = 1;
               }
          }
     }
     for(i=0;i<k;i++)
     g<<v[i]<<" ";
     f.close();g.close();
    return 0;
}
