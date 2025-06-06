#include <cstdio>
using namespace std;
FILE *f=fopen("inel.in","r");
FILE *g=fopen("inel.out","w");
int N;
int nr,i;
bool ok;
bool prim[40]={0,0,1,1,0,1,0,1,0,0, 0, 1, 0, 1, 0, 0, 0, 1, 0 ,1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 ,1, 0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 };
bool viz[40];
int rez[40];
void backtracking(int pas)
{
    if(pas<N)
    for(int i=2;i<=N;i++)
    {
        if(!viz[i]&&prim[rez[pas-1]+i])
        {
            viz[i]=1;
            rez[pas]=i;
            backtracking(pas+1);
            viz[i]=0;
        }
    }
    else
    {
        if(prim[rez[N]+1]&&prim[rez[N-1]+rez[N]])
            nr++;
    }
}
int main()
{
    fscanf(f,"%d",&N);
    viz[1]=1;
    rez[1]=1;
    if(!(N&1))
    {
        for(i=2;i<=N;i++)
        {
            if(prim[1+i])
                {rez[N]=i;
                viz[i]=1;
            backtracking(2);
            viz[i]=0;
            }
        }
    fprintf(g,"%d",nr);
    }
    else
        fprintf(g,"0");
    fclose(f);
    fclose(g);
    return 0;
}
