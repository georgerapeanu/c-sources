#include <cstdio>
using namespace std;
FILE *f,*g;
int n,k,v[16001],i,nr;
long long st,dr;
int check(int nr)
{
    int nrpasi=0,i=1,suma=0;
    while(nrpasi<=k&&i<=n)
    {
        while(v[i]+suma<=nr)
        {
            suma+=v[i];
            i++;
        }
        nrpasi++;
        suma=0;
    }
    if(nrpasi>k)
    return 0;
    return 1;
}
int main()
{
    f=fopen("transport.in","r");
    fscanf(f,"%d %d",&n,&k);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&v[i]);
        dr+=v[i];
    }
    fclose(f);
    st=1;
    while(st<dr)
    {
        nr=(st+dr)/2;
        if(check(nr)==1)
        {
            dr=nr;
        }
        else
        {
            st=nr+1;
        }
    }
    g=fopen("transport.out","w");
    fprintf(f,"%lld",st);
    fclose(g);
    return 0;
}