#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;
FILE *f=fopen("matrice4.in","r");
FILE *g=fopen("matrice4.out","w");
int N,M,X,maxim,solutii[2505],i,j,st,dr,mij,last;
bool E[33000];
int P[33000];
int main()
{
    fscanf(f,"%d %d",&N,&M);
    E[1]=E[0]=1;
    for(i=2;i<=32767;i++)
    {
        if(!E[i])
        {
            P[++P[0]]=i;
            for(j=i*i;j<=32767;j+=i)
                E[j]=1;
        }
    }
    P[++P[0]]=32771;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&X);
            st=1;
            dr=3513;
            last=-1;
            while(st<=dr)
            {
                mij=(st+dr)/2;
                if(P[mij]>=X)
                {
                    last=mij;
                    dr=mij-1;
                }
                else
                    st=mij+1;

            }
            if(P[last]-X+1>maxim)
            {
                maxim=P[last]-X+1;
                solutii[0]=1;
                solutii[1]=P[last];
            }
            else if(P[last]-X+1==maxim)
            {
                solutii[++solutii[0]]=P[last];
            }
        }
    }
    fprintf(g,"%d %d\n",maxim,solutii[0]);
    sort(solutii+1,solutii+1+solutii[0]);
    for(i=1;i<=solutii[0];i++)
        fprintf(g,"%d ",solutii[i]);
    fclose(f);
    fclose(g);
    return 0;
}
