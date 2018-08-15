#include <cstdio>
#include <vector>
#include <unordered_set>
using namespace std;
FILE *f=fopen("zeul.in","r");
FILE *g=fopen("zeul.out","w");
unordered_set<int> S;
int gr[100005];
int N;
int M;
int X,Y;
vector<pair<int,int> > rez;
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d",&X,&Y);
        gr[X]--;
        gr[Y]++;
    }
    for(int i=1;i<=N;i++)
    {
        if(gr[i]<0)
            S.insert(i);
    }
    for(int i=1;i<=N;i++)
    {
        while(gr[i]>0)
        {
            rez.push_back(make_pair(i,*(S.begin())));
            gr[*(S.begin())]++;gr[i]--;
            if(gr[*(S.begin())]==0)
                S.erase(S.begin());
        }
    }
    fprintf(g,"%d\n",rez.size());
    for(auto it:rez)
    {
        fprintf(g,"%d %d\n",it.first,it.second);
    }
    fclose(f);
    fclose(g);
    return 0;
}
