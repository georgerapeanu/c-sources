#include <cstdio>
using namespace std;
FILE *f=fopen("subsir2.in","r");
FILE *g=fopen("subsir2.out","w");
int minim,lm=5005;
int i,j;
int V[5005];
int best[5005];
int P[5005];
int N;
int ind;
bool used[5005];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        best[i]=1;
    }
    V[0]=5005;
    for(i=N;i>0;i--)
    {
        minim=5005;
        best[i]=5005;
        for(j=i+1;j<=N;j++)
        {
           if(V[i]<=V[j]&&minim>V[j])
            {
                if(best[i]>best[j]+1||(best[i]==best[j]+1&&V[P[i]]>V[j]))
                {
                    best[i]=best[j]+1;
                    P[i]=j;
                }
            }
            if(V[j]<minim&&V[j]>=V[i])
                minim=V[j];
            if(V[j]>=V[i])
                used[j]=1;
        }
        if(best[i]==5005)
            best[i]=1;
    }
    minim=5005;lm=5005;
    for(i=1;i<=N;i++)
    {
        if(!used[i]&&lm>V[i])
        {
            if(minim>best[i]||(minim==best[i]&&V[i]<V[j]))
            {
                minim=best[i];
                j=i;
            }
            ind=i;
                while(ind!=0)
                {
                    used[ind]=1;
                    ind=P[ind];
                }
        }
        if(lm>V[i])
            lm=V[i];
    }
    fprintf(g,"%d\n",minim);
    while(j!=0)
    {
        fprintf(g,"%d ",j);
        j=P[j];
    }
    fclose(f);
    fclose(g);
    return 0;
}
