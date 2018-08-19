#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("factori.in","r");
FILE *g=fopen("factori.out","w");
long long nrf,i,N,j,k,ciur[60001],val,nr;
int P[60001];
int main()
{
    ciur[0]=ciur[1]=1;
    for(i=2;i<=60001;i++)
    {
        if(ciur[i]==0)
        {
            P[++P[0]]=i;
            for(j=i*i;j<=60001;j+=i)
            {
                ciur[j]=1;
            }
        }
    }
    while(fscanf(f,"%d",&N)&&N!=0)
    {
       i=1;
       while(P[i]&&N/P[i])
       {
            val=P[i];
            nr=0;
            while(N/val)
            {
                nr+=N/val;
                val*=P[i];
            }
            fprintf(g,"%d ",nr);
            i++;
       }
       fprintf(g,"\n");
    }
   fclose(f);
   fclose(g);
    return 0;
}
