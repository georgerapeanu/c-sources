#include <cstdio>
using namespace std;
FILE *f=fopen("butoane.in","r");
FILE *g=fopen("butoane.out","w");
int sol[1005],V[1005],i,N,M,minim;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        M+=V[i];
    }
    M/=N;
    sol[2]=M-V[1]+sol[1];
    if(sol[2]<minim)
        minim=sol[2];
    for(i=3;i<N;i++)
        {sol[i]=M-V[i-1]+2*sol[i-1]-sol[i-2];if(sol[i]<minim) minim=sol[i];}

    sol[N]=V[N]-M+sol[N-1];
    if(sol[N]<minim)
        minim=sol[N];
    for(i=1;i<=N;i++)
        fprintf(g,"%d\n",sol[i]+(minim*-1));
    fclose(f);
    fclose(g);
    return 0;
}