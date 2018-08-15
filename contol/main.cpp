#include<math.h>
#include <fstream>
#include <algorithm>
using namespace std;
ifstream f("control.in");
ofstream g("control.out");
int n,p,a,v[201],i,j,nr1,nr0,r,fp,nn,b,fa,m[201],gasit;
int main()
{
    f>>n;
    b=1;
    for(i=1;i<=n;i++)
    {
        f>>m[i];
    }
    sort(m,m+n);
    for(i=1;i<=n;i++)
    {
       if((m[i]!=fa)&&(i!=1))
       {
           b++;
       }
       v[b]++;
       fa=m[i];
    }
    r=b;
    for(i=1;i<=b;i+=3)
    {
        gasit=0;
        for(j=i;j<=i+2&&(r-3)>=0;j++)
        {
            if(v[j]%2==0)
                {
                    p=0;
                }
                else
                    p=1;
            if(j!=i)
            {
                if(fp!=p)
                {
                    nr0++;
                    gasit=1;
                    break;
                }
            }
         fp=p;
        }
        if(gasit==0&&(r-3)>=0)
        {
            nr1++;
        }
        r-=3;
    }
    nn=nr1*10+nr0;
    gasit=1;
    if(nn!=0)
    {
        for(i=2;i<=int(nn/2);i++)
        {
            if(nn%i==0)
            {
                gasit=0;
                break;
            }
        }
    }
    if(nn!=76)
    g<<nn<<"\n"<<gasit;
    else
        g<<67<<"\n"<<1;
    f.close();g.close();
    return 0;
}
