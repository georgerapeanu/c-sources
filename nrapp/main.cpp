#include <cstdio>
using namespace std;
int n,v[100000];
int s(int nr)
{
    int i=0;
    for(i=nr-1;i>0;i--)
    if(v[i]<v[nr])
    return i;
    return 0;
}
int d(int nr)
{
    int i=0;
    for(i=nr+1;i<=n;i++)
    {
        if(v[i]<=v[nr])
        return i;
    }
    return n+1;
}
int main()
{
    int i=0,q=0,nr;
    char c;
    FILE *f;
    f=fopen("nrapp.in","r");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&v[i]);
    }
    fscanf(f,"%d",&q);
    FILE *g;
    g=fopen("nrapp.out","w");
    for(i=1;i<=q;i++)
    {
        fscanf(f,"%c",&c);
        fscanf(f,"%c %d",&c,&nr);
        if(c=='S')
        fprintf(g,"%d\n",s(nr));
        else
        fprintf(g,"%d\n",d(nr));
    }
    fclose(f);
    fclose(g);
    return 0;
}
