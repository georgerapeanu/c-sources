#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("secv7.in","r");
FILE *g=fopen("secv7.out","w");
int N,maxim,rez1,rez2,rez3,i1,i2,i3,J1,j2,j3,tmpmax;
int V[30001];
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        maxim=max(V[i],maxim);
    }
    rez1=rez2=rez3=(1<<30);
    tmpmax=V[N];
    for(int i=N-1;maxim!=V[i];i--)
    {
        if(rez1>V[i]+maxim+tmpmax)
        {
            rez1=V[i]+maxim+tmpmax;
            i1=i-1;
            J1=i;
        }
        tmpmax=max(tmpmax,V[i]);
    }
    tmpmax=V[1];
    for(int i=2;maxim!=V[i];i++)
    {
        if(rez2>V[i]+tmpmax+maxim)
        {
            rez2=V[i]+tmpmax+maxim;
            i2=i-1;
            j2=i;
        }
        tmpmax=max(tmpmax,V[i]);
    }

    if(maxim!=V[1]&&maxim!=V[N])
    {
        rez3=V[1]+V[N]+maxim;
        i3=1;
        j3=N-1;
    }

    if(rez1<rez2&&rez1<rez3)
    {
        fprintf(g,"%d\n%d %d",rez1,i1,J1);
    }
    else if(rez2<rez1&&rez2<rez3)
    {
        fprintf(g,"%d\n%d %d",rez2,i2,j2);
    }
    else
    {
        fprintf(g,"%d\n%d %d",rez3,i3,j3);
    }
    fclose(f);
    fclose(g);
    return 0;
}
