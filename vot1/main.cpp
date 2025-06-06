#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("vot1.in","r");
FILE *g=fopen("vot1.out","w");
queue<int> Q;
int vot[1005],N,i,V[1005],nr,a;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {fscanf(f,"%d",&V[i]);vot[V[i]]++;}
    for(i=1;i<=N;i++)
    {
        if(vot[i]==0)
            Q.push(i);
    }
    while(!Q.empty())
    {
        nr++;
        a=Q.front();
        Q.pop();
        vot[V[a]]--;
        if(vot[V[a]]==0)
            Q.push(V[a]);
    }
    fprintf(g,"%d\n",N-nr);
    for(i=1;i<=N;i++)
    {
        if(vot[i]==1)
            fprintf(g,"%d ",i);
    }
    fclose(f);
    fclose(g);
    return 0;
}
