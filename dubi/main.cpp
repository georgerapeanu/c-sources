#include <cstdio>
#include <bitset>
#include <vector>
using namespace std;
FILE *f=fopen("dubi.in","r");
FILE *g=fopen("dubi.out","w");
bitset<200005> B;
int N;
int nr;
vector<int> G[200005];
int lg2[200005];
int lg(int nr)
{
    if(!lg2[nr])
        lg2[nr]=lg(nr/2)+1;
    return lg2[nr];
}
int main()
{
    lg2[0]=-1;
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        if(B[i]==1) continue;
        int val=i,p2=lg(i)+1;
        ++nr;
        while(val<=N)
        {
            G[nr].push_back(val);
            B[val]=1;
            val+=(1<<p2);
            p2++;
        }
    }
    fprintf(g,"%d\n",nr);
    for(int i=1;i<=nr;i++)
    {
        fprintf(g,"%d ",G[i].size());
        for(auto it:G[i])
            fprintf(g,"%d ",it);
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
