#include <cstdio>
#include <queue>
#define nmax 50005
using namespace std;
FILE *f=fopen("sortaret.in","r");
FILE *g=fopen("sortaret.out","w");
queue <int> Q;
vector <int> V[nmax];
int in[nmax];
int x,y,N,M,i;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    while(M--)
    {
        fscanf(f,"%d %d",&x,&y);
        in[y]++;
        V[x].push_back(y);
    }
    for(i=1;i<=N;i++)
    {
        if(!in[i])
            Q.push(i);
    }
    while(!Q.empty())
    {
        fprintf(g,"%d ",Q.front());
        for(auto it:V[Q.front()])
        {
            in[it]--;
            if(!in[it])
                Q.push(it);
        }
        Q.pop();
    }
    fclose(f);
    fclose(g);
    return 0;
}
