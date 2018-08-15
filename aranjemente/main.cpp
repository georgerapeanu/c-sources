#include <cstdio>
#include <cstdlib>
#define MAX(A,B) A>B ? A:B
using namespace std;
FILE *f,*g;
int n,k,p,p2=1,i,resturi[70000],maxim;
void gen(bool *ptr,int pas,unsigned long long nr)
{
    if(pas==k)
    {
        long a;
        a=(nr+nr/p2)%p2;
        resturi[a]++;
    }
    else
    for(int j=0;j<n;j++)
    {
        if(ptr[j]==0)
        {
            ptr[j]=1;
            gen(ptr,pas+1,nr*10+j);
            ptr[j]=0;
        }
    }
}
int main()
{
    f=fopen("aranjamente.in","r");
    fscanf(f,"%d %d %d",&n,&k,&p);
    fclose(f);
    for(i=1;i<=p;i++)
    p2*=2;
    bool *ptr;
    ptr=(bool *) malloc(sizeof(bool)*10);
    ptr[0]=ptr[1]=ptr[2]=ptr[3]=ptr[4]=ptr[5]=ptr[6]=ptr[7]=ptr[8]=ptr[9]=0;
    gen(ptr,0,0);
    for(i=0;i<p2;i++)
    maxim=MAX(maxim,resturi[i]);
    g=fopen("aranjamente.out","w");
    fprintf(f,"%d",maxim);
    fclose(g);
    return 0;
}
