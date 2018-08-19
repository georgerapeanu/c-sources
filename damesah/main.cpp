#include <cstdio>
#include <bitset>
using namespace std;
FILE *f=fopen("damesah.in","r");
FILE *g=fopen("damesah.out","w");
int N,rez[20],nr;
bitset<30> col,pdp,pds;
bool ok;
void backtracking(int pas)
{
    if(pas==N+1)
    {
        if(!ok)
        {
            for(int i=1;i<=N;i++)
                fprintf(g,"%d ",rez[i]);
            fprintf(g,"\n");
            ok=1;
        }
        nr++;
    }
    else
    {
        for(int i=1;i<=N;i++)
        {
            if(!col[i])
            {
                if(!pdp[N-pas+i]&&!pds[pas+i-1])
                {
                    col[i]=1;
                    pdp[N-pas+i]=1;
                    pds[pas+i-1]=1;
                    rez[pas]=i;
                    backtracking(pas+1);
                    col[i]=0;
                    pdp[N-pas+i]=0;
                    pds[pas+i-1]=0;
                }
            }
        }
    }
}
int main()
{
    fscanf(f,"%d",&N);
    backtracking(1);
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
