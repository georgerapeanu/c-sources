#include <cstdio>
using namespace std;
FILE *f,*g;
int i,n,ci[100001],cf[100001],cigol,cfgol,nrpasi,gol;
int cauta(int nr)
{
    int i=1;
    while(ci[i]!=nr) i++;
    return i;
}
int main()
{
    f=fopen("album.in","r");
    g=fopen("album.out","w");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    {fscanf(f,"%d",&ci[i]);if(ci[i]==0)cigol=i;}
    for(i=1;i<=n;i++)
    {fscanf(f,"%d",&cf[i]);if(cf[i]==0)cfgol=i;}
        while(cigol!=cfgol)
        {
            gol=cauta(cf[cigol]);
            ci[cigol]=cf[cigol];
            cigol=gol;
            ci[cigol]=0;
            nrpasi++;
        }
        i=1;
        while(i<=n)
        {
        while(ci[i]==cf[i]&&i<=n+1)
        i++;
        if(i<=n)
        {
            gol=cauta(cf[i]);
            ci[cigol]=ci[i];
            ci[i]=cf[i];
            cigol=gol;
            ci[cigol]=0;
            nrpasi++;
        }
        }
    fprintf(g,"%d",nrpasi);
    fclose(g);
    fclose(f);
    return 0;
}