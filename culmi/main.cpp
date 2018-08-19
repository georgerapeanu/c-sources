#include <cstdio>
using namespace std;
FILE *f=fopen("culmi.in","r");
FILE *g=fopen("culmi.out","w");
int V[10050];
int i,j,nr,rez,N;
bool rezolvat;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&nr);
        rezolvat=0;
        for(j=1;j<=rez&&!rezolvat;j++)
        {
            if(V[j]<nr)
            {
                V[j]=nr;
                rezolvat=1;
            }
        }
        if(!rezolvat)
        {
            V[++rez]=nr;
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
