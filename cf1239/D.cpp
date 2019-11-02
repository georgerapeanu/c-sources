#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;

int t;
int n,m;
vector<vector<int>> graph;
vector<vector<int>> graphT;
int viz[NMAX + 5];

int cnt;

void solve(int nod,const vector<vector<int>> &graph) {
    cnt++;
    for(auto it:graph[nod]) {
        if(viz[it] == 0) {
            viz[it] = nod;
        }
    }

    for(auto it:graph[nod]) {
        if(viz[it] == nod) {
            solve(it,graph);
        }
    }
}

void afis(vector<int> &jud,vector<int> &cat) {
    printf("Yes\n%d %d\n",jud.size(),cat.size());
    for(auto it:jud)printf("%d ",it);
    printf("\n");
    for(auto it:cat)printf("%d ",it);
    printf("\n");
}

int main() {

    graphT = graph = vector<vector<int> >(NMAX + 5,vector<int>());

    scanf("%d",&t);

    while(t--) {
        scanf("%d %d",&n,&m);

        for(int i = 1; i <= n; i++) {
            graph[i].clear();
            graphT[i].clear();
            viz[i] = true;
        }

        for(int i = 1; i <= m; i++) {
            int u,v;
            scanf("%d %d",&u,&v);
            graph[u].push_back(v);
            graphT[v].push_back(u);
        }

        int nod = 1;

        for(int i = 1; i <= n; i++) {
            viz[i] = 0;
        }

        cnt = 0;

        viz[1] = -1;
        solve(1,graph);

        if(cnt < n) {
            vector<int> jud;
            vector<int> cat;
            for(int i = 1; i <= n; i++) {
                if(viz[i] != 0) {
                    jud.push_back(i);
                }
                else {
                    cat.push_back(i);
                }
            }

            afis(jud,cat);
            continue;
        }
        else {
            for(int i = 1; i <= n; i++) {
                viz[i] = 0;
            }
            cnt = 0;
            viz[1] = -1;
            solve(1,graphT);
            if(cnt < n) {
                vector<int> jud;
                vector<int> cat;

                for(int i = 1; i <= n; i++) {
                    if(viz[i] != 0) {
                        cat.push_back(i);
                    }
                    else {
                        jud.push_back(i);
                    }
                }

                afis(jud,cat);
                continue;
            }
            else {
                printf("No\n");
            }
        }
    }

    return 0;
}
