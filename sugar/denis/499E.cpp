#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class MaxFlowSolver {
public:
    int S,D;
    vector<vector<int> > F;
    vector<vector<int> > C;
    vector<bool> viz;
    vector<int> T;
    vector<int> Q;
    int stq,drq;
    vector< vector<int> > G;

    MaxFlowSolver(int n) {
        n += 3;
        S = 0;
        D = n - 1;
        F.resize(n);
        C.resize(n);
        viz.resize(n);
        T.resize(n);
        Q.resize(n);
        stq = drq = 0;
        G.resize(n);
        for(int i = 0; i < n; i++) {
            F[i].resize(n);
            C[i].resize(n);
            G[i].resize(n);
        }
    }

    void add_edge(int u,int v,int w) {
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
                for(int nod=D; nod!=S; nod=T[nod])fmin=min(fmin,C[T[nod]][nod]-F[T[nod]][nod]);
                if(!fmin)continue;
                for(int nod=D; nod!=S; nod=T[nod]) {
                    F[T[nod]][nod]+=fmin;
                    F[nod][T[nod]]-=fmin;
                }
                flow+=fmin;
            }
        }
        return flow;
    }

};

const int NMAX = 100;

int n,m;
int a[NMAX + 5];
int u[NMAX + 5];
int v[NMAX + 5];
int cnt[NMAX + 5];

vector<int> primes;

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        int ba = a[i];
        for(int j = 2; 1LL * j * j <= a[i]; j++) {
            if(a[i] % j == 0) {
                primes.push_back(j);
                while(a[i] % j == 0) {
                    a[i] /= j;
                }
            }
        }
        if(a[i] != 1) {
            primes.push_back(a[i]);
        }
        a[i] = ba;
    }

    sort(primes.begin(),primes.end());
    primes.resize(unique(primes.begin(),primes.end()) - primes.begin());

    for(int j = 1; j <= m; j++) {
        scanf("%d %d",&u[j],&v[j]);
        if(u[j] % 2 == 1) {
            swap(u[j],v[j]);
        }
    }

    int ans = 0;

    for(auto it:primes) {
        MaxFlowSolver tmp(n + 4);
        for(int i = 1; i <= n; i++) {
            cnt[i] = 0;
            while(a[i] % it == 0) {
                cnt[i]++;
                a[i] /= it;
            }
            if(cnt[i]) {
                if(i % 2 == 0)tmp.add_edge(tmp.S,i,cnt[i]);
                else          tmp.add_edge(i,tmp.D,cnt[i]);
            }
        }

        for(int i = 1; i <= m; i++) {
            tmp.add_edge(u[i],v[i],100);
        }

        ans += tmp.maxflow();
    }

    printf("%d\n",ans);

    return 0;
}