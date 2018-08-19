#include <cstdio>
#include <vector>
#define nod first
#define cost second
#define inf (1<<30)
using namespace std;
FILE *f=fopen("hamilton.in","r");
FILE *g=fopen("hamilton.out","w");
int N;
int M,D[(1<<18)][18];
int x,y,z;
vector<pair<int,int> > Gt[18];
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d%d",&x,&y,&z);
        Gt[y].push_back(make_pair(x,z));
    }
    for(int i=(1<<18)-1;i>=0;i--)
        for(int j=0;j<N;j++) D[i][j]=inf;
    D[1][0]=0;
    for(int i=3;i<(1<<18);i+=2)
    {
        for(int j=1;j<N;j++)
        {
            if(i&(1<<j))
            {
                for(auto it:Gt[j])
                {
                    if((1<<(it.nod))&i)
                    {
                        D[i][j]=min(D[i-(1<<j)][it.nod]+it.cost,D[i][j]);
                    }
                }
            }
        }
    }
    int rez=inf;
    for(auto it:Gt[0])
    {
        rez=min(rez,D[(1<<N)-1][it.nod]+it.cost);
    }
    if(rez!=inf)
        fprintf(g,"%d",rez);
    else
        fprintf(g,"Nu exista solutie");
    fclose(f);
    fclose(g);
    return 0;
}
