#include <cstdio>
using namespace std;
FILE *f=fopen("echilibru.in","r");
FILE *g=fopen("echilibru.out","w");
bool sol;
int S,V[20],N,i,T,j,rez;
void backtracking(int pas,int nrok,int suma)
{
    if(nrok==N)
    {
        if(suma==S-suma)
            sol=1;
    }
    if(pas>2*N)
        ;
    else
    {
        if(!sol)
        {
            backtracking(pas+1,nrok+1,suma+V[pas]);
        }
        if(!sol)
        {
            backtracking(pas+1,nrok,suma);
        }
    }
}
int main()
{
    fscanf(f,"%d",&T);
    for(i=1;i<=T;i++)
    {
        fscanf(f,"%d",&N);
        S=0;
        for(j=1;j<=2*N;j++)
            {fscanf(f,"%d",&V[j]);S+=V[j];}
        sol=0;
        if(S%2==0)
        backtracking(1,0,0);
        rez=(rez<<1)+sol;
    }
    fprintf(g,"%d",rez);
    return 0;
}
