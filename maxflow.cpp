#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define maxN 1005
using namespace std;
FILE *f=fopen("maxflow.in","r");
FILE *g=fopen("maxflow.out","w");
int N,M;

class MaxFlowSolver{
public:
	int S,D;
	vector<vector<int> > F;
	vector<vector<int> > C;
 	vector<bool> viz;
	vector<int> T;
	vector<int> Q;
	int stq,drq;
	vector< vector<int> > G;

	MaxFlowSolver(int n){
		n += 3;
		S = 0;D = n - 1;
		F.resize(n);
		C.resize(n);
		viz.resize(n);
		T.resize(n);
		Q.resize(n);
		stq = drq = 0;
		G.resize(n);
		for(int i = 0;i < n;i++){
			F[i].resize(n);
			C[i].resize(n);
			G[i].resize(n);
		}
	}
	
	void add_edge(int u,int v,int w){
		G[u].push_back(v);
		G[v].push_back(u);
		C[u][v] += w;
	}

	bool BFS(int S,int D)
	{
		Q[stq=drq=1]=S;
		fill(viz.begin(),viz.end(),0);
		viz[S]=1;
		while(stq<=drq)
		{
			int nod=Q[stq++];
			if(nod==D)continue;
			for(auto it:G[nod])
			{
				if(!viz[it]&&F[nod][it]<C[nod][it])
				{
					viz[it]=1;
					T[it]=nod;
					Q[++drq]=it;
				}
			}
		}
		return viz[D];
	}
	
	int maxflow()
	{
		int flow=0;
		while(BFS(S,D))
		{
			for(auto it:G[D])
			{
				if(!viz[it]||F[it][D]==C[it][D])continue;
				int fmin=1<<30;
				T[D]=it;
				for(int nod=D;nod!=S;nod=T[nod])fmin=min(fmin,C[T[nod]][nod]-F[T[nod]][nod]);
				if(!fmin)continue;
				for(int nod=D;nod!=S;nod=T[nod]){F[T[nod]][nod]+=fmin;F[nod][T[nod]]-=fmin;}
				flow+=fmin;
			}
		}
		return flow;
	}

};

int main()
{
    fscanf(f,"%d %d",&N,&M);
	MaxFlowSolver net(N);
	for(int i=1;i<=M;i++)
    {
        int x,y,z;
        fscanf(f,"%d %d %d",&x,&y,&z);
        net.add_edge(x,y,z);
    }
	net.S = 1;
	net.D = N;
    fprintf(g,"%d",net.maxflow());
    fclose(f);
    fclose(g);
    return 0;
}