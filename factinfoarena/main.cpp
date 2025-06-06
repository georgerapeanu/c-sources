#include <cstdio>
#define mij(A,B) (A+B)/2
using namespace std;
FILE *f=fopen("fact.in","r");
FILE *g=fopen("fact.out","w");
int P,st=1,dr=1000000000,last=1000000001;
int ok(int val)
{
    int K=5,suma=0;
    while(K<=val)
    {
        suma+=val/K;
        K=K*5;
        if(suma>P)
            return 1;
    }
    if(suma<P)
        return -1;
    return 0;
}
int main()
{
    fscanf(f,"%d",&P);
    while(st<=dr)
    {
        if(ok(mij(st,dr))==0)
        {
            last=mij(st,dr);
            dr=mij(st,dr)-1;
        }
        else if(ok(mij(st,dr))==-1)
            st=mij(st,dr)+1;
        else
            dr=mij(st,dr)-1;
    }
    if(last==1000000001)
        fprintf(g,"-1");
    else
    fprintf(g,"%d",last);
    return 0;
}
