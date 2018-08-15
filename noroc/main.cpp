#include <cstdio>
using namespace std;
FILE *f=fopen("noroc.in","r");
FILE *g=fopen("noroc.out","w");
int N,V[201],i,j,S[201],x=1,y;
bool gasit;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {fscanf(f,"%d",&V[i]);S[i]=(S[i-1]+V[i]*V[i])%N;if(!S[i]){gasit=1;y=i;}}
    if(!gasit)
    {
        for(i=1;i<=N&&!gasit;i++)
            for(j=i+1;j<=N&&!gasit;j++)
                if((S[j]-S[i-1])==0){x=i;y=j;gasit=1;}
    }
    fprintf(g,"%d\n",y-x+1);
    for(i=x;i<=y;i++)
        fprintf(g,"%d ",V[i]);
    fclose(f);
    fclose(g);
    return 0;
}
