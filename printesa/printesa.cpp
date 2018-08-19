#include<fstream>
using namespace std;
ifstream f("printesa.in");
ofstream g("printesa.out");
int main()
{
    int k,h,i,j,p=2,d,c,e,b=1,q=0;
    f>>k;
    f>>h;
    int v[h],z[k];
    for(i=0;i<h;i++)
    {
        f>>v[i];
    }
    for(c=2;c<=100;c++)
    {
    for(j=1;j<=c/2;j++)
    {
        if(c%j!=0)
            d=1;
            else if(j==c)
                d=1;
            else if(j==1)
                d=1;
        else
        {
            d=0;
            j=c;
        }
    }
    if(d==1)
    {
        for(i=0;i<h;i++)
        {
            if(c!=v[i])
                e=1;
            else
            {
                e=0;
                i=h;
            }
        }
        if(e==1&&b<=k)
        {
            b++;
            z[q]=c;
            q++;
        }
    }
    }
     for(i=k-1;i>=0;i--)
    {
        g<<z[i]<<" ";
    }
    return 0;
        }
