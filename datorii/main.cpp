#include <cstdio>
#define zeros(x) (x^(x-1))&x
using namespace std;
FILE *f=fopen("datorii.in","r");
FILE *g=fopen("datorii.out","w");
int N,M,V[15500],i,j,AIB[15500],x,y;
bool c;
void add(int poz,int quantity)
{
    for(j=poz;j<=N;j+=zeros(j))
        AIB[j]+=quantity;
}
int  compute(int poz)
{
    int rez=0;
    for(j=poz;j>0;j-=zeros(j))
        rez+=AIB[j];
    return rez;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {fscanf(f,"%d",&V[i]);add(i,V[i]);}
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d %d",&c,&x,&y);
        if(c)
            fprintf(g,"%d\n",compute(y)-compute(x-1));
        else
            add(x,-1*y);
    }
    return 0;
}
