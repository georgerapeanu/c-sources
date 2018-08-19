#include <cstdio>
#define nmax 100005
using namespace std;
FILE *f=fopen("intersort.in","r");
FILE *g=fopen("intersort.out","w");
int V[nmax];
int N,val;
int nr[nmax],op;
int i,j;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        V[val]=i;
    }
    for(i=1;i<=N;i++)
    {
        if(V[i]!=i)
        {
            j=i;
            nr[0]=0;
            while(V[j]!=i)
            {
                nr[++nr[0]]=j;
                j=V[j];
            }
            nr[++nr[0]]=j;
            if(nr[0]==2&&nr[1]==2)
            {
                op+=2;
            }
            else if(V[1]==1)
            {
                op+=nr[0]+1;
            }
            else
            {
                op+=nr[0]-1;
            }
            for(j=1;j<=nr[0];j++)
            {
                V[nr[j]]=nr[j];
            }
        }
    }
    fprintf(g,"%d",op);
    fclose(f);
    fclose(g);
    return 0;
}
