#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("zigzag.in","r");
FILE *g=fopen("zigzag.out","w");
int dist;
int i,j,C,N,nr=1;
char c[50005];
short pas=1;
vector <char> V[5005];
int main()
{
    fscanf(f,"%d %d\n",&C,&N);
    fgets(c+1,50005,f);
    dist=2*C-2;
    if(C>N)
        C=N;
    for(i=1;i<=C;i++)
    {
        j=i;
        while(j<=N)
        {
            if(dist!=0)
                V[i].push_back(c[nr++]);
            j+=dist;
            if(j<=N)
                V[i].push_back(c[nr++]);
            j+=2*C-2-dist;
            if(i==1)
                j+=dist;
        }
        dist-=2;
    }
    j=1;
    for(i=1;i<=N;i++)
    {
        c[i]=V[j][0];
        V[j].erase(V[j].begin());
        j+=pas;
        if(j<1||j>C)
        {
            pas*=-1;
            j+=2*pas;
        }
    }
    fputs(c+1,g);
    fclose(f);
    fclose(g);
    return 0;
}
