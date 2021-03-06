#include <cstdio>
#define zeros(x) x&(x^(x-1))
using namespace std;
FILE *f=fopen("jeton.in","r");
FILE *g=fopen("jeton.out","w");
int N,M,minim=50005,maxim,i,rez1,rez2,valmax=50005;
int F[50005];
int A[50005],B[50005];
int val;
void add(int poz,int cant,int frecv[])
{
    for(int i=poz;i<=valmax;i+=zeros(i))
        frecv[i]+=cant;
}
int compute(int poz,int frecv[])
{
    int rez=0;
    for(int i=poz;i>0;i-=zeros(i))
        rez+=frecv[i];
    return rez;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        add(val,1,A);
        F[val]++;
    }
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d",&val);
        add(val,1,B);
        F[val]++;
        if(F[val]==2)
        {
            if(val<minim)
                minim=val;
            if(val>maxim)
                maxim=val;
        }
    }
    fprintf(g,"%d %d ",minim,maxim);
    rez1=compute(maxim,A)-compute(minim-1,A);
    rez2=compute(maxim,B)-compute(minim-1,B);
    rez1=N-rez1;
    rez2=M-rez2;
    if(rez1==rez2)
        fprintf(g,"0");
    else if(rez1>rez2)
        fprintf(g,"1");
    else
        fprintf(g,"2");
    fclose(f);
    fclose(g);
    return 0;
}
