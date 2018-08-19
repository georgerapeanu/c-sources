#include <cstdio>
#include <cstring>
#define S short
using namespace std;
FILE *f,*g;
S rest[]={1,3,2,6,4,5},suma,lim,i,restx;
char c[200];
int main()
{
  f=fopen("petale.in","r");
  fscanf(f,"%s",&c);
  fclose(f);
  lim=strlen(c);
  for(i=0;i<lim;i++)
  {
        if(c[i]=='0')
        {
            continue;
        }
        else if(c[i]=='1')
        {suma+=rest[(lim-i-1)%6];suma%=7;}
        else if(c[i]=='2')
        {
         suma+=2*rest[(lim-i-1)%6];suma%=7;
        }
        else
        restx=rest[(lim-i-1)%6];
  }
  g=fopen("petale.out","w");
  if(suma==0)
  fprintf(g,"0");
  else if(7-suma==restx)
  fprintf(g,"1");
  else if(7-suma==(restx*2)%7)
  fprintf(g,"2");
  else
  fprintf(g,"-1");
}
