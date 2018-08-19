#include <cstdio>
#include <stack>
using namespace std;
FILE *f=fopen("maxk.in","r");
FILE *g=fopen("maxk.out","w");
int frecv[100005],i,j,minim=9999999999,N,V[100005],K,mv;
stack <int>uneok;
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=N;i++)
        {fscanf(f,"%d",&V[i]);frecv[V[i]]++;if(V[i]>mv)mv=V[i];}
    for(i=1;i<=mv;i++)
        if(frecv[i]>K)
        uneok.push(i);

    i=0;j=0;
    while(j<=N)
    {
      if(uneok.empty())
      {
          if(j-i<minim)
          {minim=j-i;}
          i++;
          frecv[V[i]]++;
          if(frecv[V[i]]>K)
            uneok.push(V[i]);
      }
      else
      {
          j++;
        frecv[V[j]]--;
        while(!uneok.empty()&&frecv[uneok.top()]<=K)
            uneok.pop();
      }
    }
    fprintf(g,"%d",minim);
    fclose(f);
    fclose(g);
    return 0;
}
