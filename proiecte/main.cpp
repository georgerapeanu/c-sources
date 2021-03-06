#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("proiecte.in","r"),*g;
int maxim=0,n,m,i,nri;
int firme[1000005],V[200005];
int calcul(int nri)
{
    int candidat=0,nrap=0;
  for(int i=1;i<=nri;i++)
  {
      fscanf(f,"%d",&V[i]);
      if(V[i]!=candidat)
        nrap--;
      else
        nrap++;
      if(nrap<0)
      {
          candidat=V[i];
          nrap=1;
      }
  }
  nrap=0;
  for(int i=1;i<=nri;i++)
    nrap+=(V[i]==candidat);
  if(nrap>nri/2)
    return candidat;
  return 0;
}
int main()
{
    fscanf(f,"%d %d",&n,&m);
    for(i=1;i<=m;i++)
    {
        fscanf(f,"%d",&nri);
        firme[calcul(nri)]++;
    }
    fclose(f);
    for(i=1;i<=n;i++)
    {
        maxim=maxim>firme[i] ? maxim:firme[i];
    }
    g=fopen("proiecte.out","w");
    for(i=1;i<=n;i++)
    {
        if(firme[i]==maxim)
        {
            fprintf(g,"%d ",i);
        }
    }
    fclose(g);
    return 0;
}
