#include <cstdio>
#include <cstdio>
using namespace std;
FILE *f=fopen("permutari.in","r");
FILE *g=fopen("permutari.out","w");
int N;
bool viz[10];
int rez[10];
void backtracking(int pas)
{
    if(pas<=N)
    for(int i=1;i<=N;i++)
    {
        if(!viz[i])
        {
            viz[i]=1;
            rez[pas]=i;
            backtracking(pas+1);
            viz[i]=0;
        }
    }
    else
    {
        for(int i=1;i<=N;i++)
            fprintf(g,"%d ",rez[i]);
        fprintf(g,"\n");
    }
}
int main()
{
    fscanf(f,"%d",&N);
    backtracking(1);
    fclose(f);
    fclose(g);
    return 0;
}
