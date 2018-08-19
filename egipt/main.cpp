#include <cstdio>
#include <vector>
#include <unordered_set>
#define mp make_pair
#define pb push_back
using namespace std;
FILE *f=fopen("egipt.in","r");
FILE *g=fopen("egipt.out","w");
int nr[4],N;
int V[10005];
int inv;
unordered_set<int> t[4][4];
vector<pair<int,int> > sw;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        nr[V[i]]++;
    }
    for(int i=1;i<4;i++) nr[i]+=nr[i-1];
    for(int i=1;i<4;i++)
    {
        for(int j=nr[i-1]+1;j<=nr[i];j++)
            t[i][V[j]].insert(j);
    }
    for(int i=1;i<4;i++)
    {
        for(int j=nr[i-1]+1;j<=nr[i];j++)
        {
            if(V[j]==i) continue;
            if(!t[V[j]][i].empty())
            {
                sw.pb(mp(j,*(t[V[j]][i].begin())));
                t[V[j]][i].erase(*t[V[j]][i].begin());
                t[i][V[j]].erase(j);
            }
            else
            {
                int cel=(V[j]^i);
                sw.pb(mp(j,*(t[cel][i].begin())));
                t[cel][V[j]].insert(*t[cel][i].begin());
                t[cel][i].erase(*t[cel][i].begin());
                t[i][V[j]].erase(j);
            }
            swap(V[sw[inv].first],V[sw[inv].second]);
            inv++;
        }
    }
    fprintf(g,"%d\n",inv);
    for(auto it:sw)
        fprintf(g,"%d %d\n",it.first,it.second);
    fclose(f);
    fclose(g);
    return 0;
}
