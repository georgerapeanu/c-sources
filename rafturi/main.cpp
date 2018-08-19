#include <cstdio>
using namespace std;
FILE *f,*g;
long long c,n,v[50001],a,b,i,inaltime[10001],h,j;
int main()
{
    f=fopen("rafturi.in","r");
    fscanf(f,"%d %d",&c,&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d %d",&a,&b);
        v[a]= v[a]>b ? v[a]:b;
    }
    fclose(f);
    for(i=1;i<=c;i++)
    {
          h=v[i];
          inaltime[i]=inaltime[i-1]+h;
          for(j=i-1;j>i-3&&j>0;j--)
          {
              if(v[j]>h)h=v[j];
              if(inaltime[j-1]+h<inaltime[i])
              inaltime[i]=inaltime[j-1]+h;
          }
    }
    g=fopen("rafturi.out","w");
    fprintf(g,"%d",inaltime[c]);
    fclose(g);
    return 0;
}
