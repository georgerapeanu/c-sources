#include <cstdio>
#include <cstring>
using namespace std;
char a,b,c,m[999997][4],v[4];
FILE *f,*g;
long long i,n,frecv[999997],maxim,nrmax;
bool gasit=0;
int main()
{
    f=fopen("trigrame.in","r");
    g=fopen("trigrame.out","w");
    a=fgetc(f);
    b=fgetc(f);
    c=fgetc(f);
    n++;
    m[0][0]=a;
    m[0][1]=b;
    m[0][2]=c;
    while(c!=-1&&c!='\n')
    {
        a=b;
        b=c;
        c=fgetc(f);
        if(c!=-1&&c!='\n')
        {
        v[0]=a;
        v[1]=b;
        v[2]=c;
        gasit=0;
        for(i=0;i<n;i++)
        {
            if(strcmp(m[i],v)==0)
            {
                gasit=1;
                frecv[i]++;
                break;
            }
        }
        if(gasit==0)
        {
            n++;
            m[n-1][0]=a;
            m[n-1][1]=b;
            m[n-1][2]=c;
        }
        }
    }
    for(i=0;i<n;i++)
    {
       if(frecv[i]>maxim)
       {maxim=frecv[i];nrmax=1;}
       else if(frecv[i]==maxim)
       nrmax++;
    }
    maxim++;
    fprintf(g,"%lld %lld %lld",n,maxim,nrmax);
    fclose(f);
    fclose(g);
    return 0;
}
