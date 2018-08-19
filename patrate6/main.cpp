#include <cstdio>
using namespace std;
FILE *f=fopen("patrate6.in","r");
FILE *g=fopen("patrate6.out","w");
int i,N;
int a[1005];
int b[1005];
int c[1005];
int tmp[1005];
void shl(int V[])
{
    for(int i=1;i<V[0];i++)
        V[i]=V[i+1];
    V[0]--;
}
void shr(int V[])
{
    for(int i=V[0]+1;i>1;i--)
        V[i]=V[i-1];
    V[0]++;
    V[1]=0;
}
void copiere(int a[],int b[])
{
    for(int i=0;i<=b[0];i++)
        a[i]=b[i];
}
void scadere(int a[],int b[])
{
    while(b[0]<a[0])
        shr(b);
    for(int i=a[0];i>0;i--)
    {
        a[i]-=b[i];
        if(a[i]<0)
        {
            a[i]+=10;
            a[i-1]--;
        }
    }
    while(a[1]==0&&a[0]>1)
        shl(a);
    while(b[1]==0&&b[0]>1)
        shl(b);
}
void inmultire(int a[],int val)
{
    for(int i=a[0];i>=1;i--)
    {
        a[i]*=val;
    }
    for(int i=a[0];i>1;i--)
    {
        a[i-1]+=a[i]/10;
        a[i]%=10;
    }
    while(a[1]>9)
    {
        shr(a);
        a[1]=a[2]/10;
        a[2]%=10;
    }
}
int main()
{
    fscanf(f,"%d",&N);
    i=2;
    a[0]=1;a[1]=0;
    b[0]=1;b[1]=1;
    c[0]=1;c[1]=5;
    while(i<N)
    {
        copiere(a,b);
        copiere(b,c);
        copiere(c,b);
        inmultire(c,5);
        copiere(tmp,a);
        inmultire(tmp,2);
        scadere(c,tmp);
        i++;
    }
    for(i=1;i<=c[0];i++)
        fprintf(g,"%d",c[i]);
    fclose(f);
    fclose(g);
    return 0;
}
