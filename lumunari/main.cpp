#include <cstdio>
#include <algorithm>
#define mij(A,B) (A+B)/2
using namespace std;
FILE *f=fopen("lumanari.in","r");
FILE *g=fopen("lumanari.out","w");
long long M,L[200005],i,st,dr,last,suma;
bool ok(int val)
{
  long long clum=0,poz=M,sum=0;
  for(int i=val;i>0;i--)
  {
      clum+=i;
      clum=max(0LL,clum-L[poz]);///incercam sa umplem I cu lumanarea, clum va fi cat ne mai trebuie ca sa umplem
      poz--;
  }
  for(int i=poz;i>=1;i--)
    sum+=L[i];///putem suda celelalte lumanari ca sa umple clum
  if(sum>=clum)
    return true;
  return false;
}
int main()
{
    fscanf(f,"%lld",&M);
    for(i=1;i<=M;i++)
        {fscanf(f,"%lld",&L[i]);suma+=L[i];}
   sort(L+1,L+1+M);
    st=1;
    dr=M;
    while(st<=dr)
    {
        if(ok(mij(st,dr)))
            {last=mij(st,dr);st=mij(st,dr)+1;}
        else
            dr=mij(st,dr)-1;
   }
   fprintf(g,"%lld",last);
    return 0;
}
