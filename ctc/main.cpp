#include <cstdio>
#include <algorithm>
#include <bitset>
#include <vector>
using namespace std;
FILE *f=fopen("ctc.in","r");
FILE *g=fopen("ctc.out","w");
int lvl[100005],len;
vector <int> graph[100005];
vector<vector<int> > compo;
int low[100005];
int st[100005];
int viz[100005];
bool inst[100005];
int i,N,M,x,y,nr;
int lastid;

void ctc(int nod) {
    low[nod] = lvl[nod] = ++lastid;
    viz[nod] = 1;
    st[++len] = nod;
    inst[st[len]] = true;

    for(auto it:graph[nod]) {
        if(!viz[it]) {
            ctc(it);
        }

        if(inst[it]) {
            low[nod] = min(low[nod],low[it]);
        }
    }

    if(low[nod] == lvl[nod]) {
		vector<int> comp;
        while(st[len] != nod) {
			comp.push_back(st[len]);
			inst[st[len]] = false;
			len--;
        }
		comp.push_back(st[len]);
		inst[st[len]] = false;
		compo.push_back(comp);
        len--;
    }
}

int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        graph[x].push_back(y);
    }
    for(int i=1;i<=N;i++)if(!viz[i])ctc(i);
    fprintf(g,"%d\n",compo.size());
    for(auto i:compo)
    {
        for(auto it:i)
            fprintf(g,"%d ",it);
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
