#include<iostream>
#include<fstream>
using namespace std;
ifstream f("joc.in");
ofstream g("joc.out");
int main()
{
    long x,y,d,l,p,o,a=1,s=1,m,n,k,i,c,t,uc=10,r;
    f>>x;
    f>>y;
    d=x;
    l=y;
    while(d!=0)
    {
        d=d/10;
        a=a*10;
    }
      while(l!=0)
    {
        l=l/10;
        s=s*10;
    }
    m=x*s+y;k=m;p=k;
    n=y*a+x;i=n;t=i;
    if(k%2==0)
    {
        while(k!=0)
        {
            c=k%10;
            k=k/10;
            if(c<=uc)
            {
                uc=c;
                o=1;
            }
            else
                o=0;
             if(o==0)
                 k=0;
        }
    }
        if(o==0)
        {
            uc=0;
        if(p%2==0)
        {
        while(p!=0)
        {
            c=p%10;
            p=p/10;
            if(c>=uc)
            {
                uc=c;
                o=1;
            }
            else
                o=0;
                if(o==0)
                k=0;
        }
        }
        }
        else
            o=0;
      if(t%2==0)
    {
        uc=10;
        while(t!=0)
        {
            c=t%10;
            t=t/10;
            if(c<=uc)
            {
                uc=c;
                r=1;
            }
            else
                r=0;
             if(r==0)
                 t=0;
        }
    }
        if(r==0)
        {
            uc=0;
        if(i%2==0)
        {
        while(i!=0)
        {
            c=i%10;
            i=i/10;
            if(c>=uc)
            {
                r=1;
                uc=c;
            }
            else
                r=0;
                if(r==0)
                    i=0;
        }

    }
        }
    if(r==0&&o==0)
        g<<"0";
    else if(r==1&&o==0)
        g<<n;
    else if(r==0&&o==1)
        g<<m;
    else if(r==1&&o==1)
        g<<n<<endl<<m;
        f.close();g.close();
    return 0;
}