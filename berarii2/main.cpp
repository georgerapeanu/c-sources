#include <cstdio>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;
FILE *f=fopen("berarii2.in","r");
FILE *g=fopen("berarii2.out","w");
int N,M,K;
vector <int> V[1000005];
int i;
queue <int> Q;
bitset <1000005> B;
int nr;
int x,y;
int main()
{
    fscanf(f,"%d%d%d",&N,&M,&K);
    for(i=1;i<=M;i++)
    {
       fscanf(f,"%d %d",&x,&y);
       V[y].push_back(x);
    }
    for(i=1;i<=K;i++)
    {
        fscanf(f,"%d",&x);
        B[x]=1;
        Q.push(x);
    }
    while(!Q.empty())
    {
        nr++;
        x=Q.front();
        Q.pop();
        for(auto it:V[x])
            if(B[it]==0)
            {
                Q.push(it);
                B[it]=1;
            }
    }
    fprintf(g,"%d\n",N-nr);
    for(i=1;i<=N;i++)
        if(B[i]==0)
            fprintf(g,"%d\n",i);
    fclose(f);
    fclose(g);
    return 0;
}
