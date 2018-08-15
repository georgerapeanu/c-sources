#include <cstdio>
#include <vector>
using namespace std;
FILE *f=fopen("grarb.in","r");
FILE *g=fopen("grarb.out","w");
bool viz[100005];
vector <int> V[100005];
int N,i,u,v;
long long M;
long long cnt=1;
long long elem[100005];
long long S;
void dfs(int nod)
{
    elem[cnt]++;
    for(vector<int>::iterator it=V[nod].begin();it!=V[nod].end();it++)
    {
        if(!viz[*it])
        {
            viz[*it]=1;
            dfs(*it);
        }
    }
}
int main()
{
    fscanf(f,"%d %lld",&N,&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&u,&v);
        V[u].push_back(v);
        V[v].push_back(u);
    }
    for(i=1;i<=N;i++)
    {
        if(!viz[i])
        {
            viz[i]=1;
            dfs(i);
            S+=elem[cnt]-1;
            cnt++;
        }
    }
    cnt--;
    fprintf(g,"%lld\n%lld",M-S,cnt-1);
    fclose(f);
    fclose(g);
    return 0;
}
