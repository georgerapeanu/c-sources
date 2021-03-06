#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("euro2.in","r"),*g=fopen("euro2.out","w");
int dr[10005],st[10005],N,i,j,maxim,S,D,M,L,smax,dmax,bst[10005],bdr[10005];
double V[10005];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lf",&V[i]);
        S=1;
        D=smax;
        L=0;
        while(S<=D)
        {
            M=(S+D)/2;
            if(V[st[M]]<=V[i])
            {
                L=M;
                S=M+1;
            }
            else
                D=M-1;
        }
        if(L+1>smax)
        {
            st[++smax]=i;
        }
        else
            if(V[st[L+1]]>V[i])
                st[L+1]=i;
        bst[i]=L+1;
    }
    for(i=N;i>0;i--)
    {
        S=1;
        D=dmax;
        L=0;
        while(S<=D)
        {
            M=(S+D)/2;
            if(V[dr[M]]<=V[i])
            {
                L=M;
                S=M+1;
            }
            else
                D=M-1;
        }
        if(L+1>dmax)
        {
            dr[++dmax]=i;
        }
        else
            if(V[dr[L+1]]>V[i])
                dr[L+1]=i;
        bdr[i]=L+1;
    }
    for(i=1;i<=N;i++)
    {
        if(bst[i]>=2&&bdr[i]>=2)
            maxim=max(bst[i]+bdr[i]-1,maxim);
    }
    fprintf(g,"%d ",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
