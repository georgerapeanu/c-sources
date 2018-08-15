#include<fstream>
using namespace std;
ifstream f("cifru4.in");
ofstream g("cifru4.out");
unsigned long long int ca,a,v[10],p10=1,nc=1,i,j,m[10],k,x,y;
int main()
{
    f>>a;
    ca=a;
    while(ca>9)
    {
        ca=ca/10;
        p10*=10;
        nc++;
    }
    j=1;
    k=1;
     for(i=p10;i>=1;i/=10)
     {
        v[j]=a/i;
        if(v[j]%nc==0)
            x++;
        else
        {
            m[k]=v[j];
            k++;
        }
        j++;
     }
     k--;
     for(i=1;i<=k;i++)
     {
         for(j=k;j>i;j--)
         {
             if((m[j]-m[i])%nc==0)
                y++;
         }
     }
     x+=y;
     g<<x;
     f.close();g.close();
    return 0;
}
