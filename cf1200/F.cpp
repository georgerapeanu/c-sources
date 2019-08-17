#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1000;
const int LMAX = 2520;

int ans[NMAX + 1][LMAX + 1];
int viz[NMAX + 1][LMAX + 1];

int n;
vector<int> graph[NMAX + 1];
int sz[NMAX + 5];
int k[NMAX + 5];
bool used[NMAX + 5];

int get_mod(int x) {
    return ((x % LMAX) + LMAX) % LMAX;
}

void solve(int x,int y) {
    vector<pair<int,int> > states;

    states.push_back({0,0});

    viz[x][y] = states.size();
    states.push_back({x,y});

    while(true) {
        y = get_mod(y + k[x]);
        x = graph[x][y % sz[x]];

        if(viz[x][y] != 0) {
            if(viz[x][y] < (int)states.size() && states[viz[x][y]] == make_pair(x,y)) {
                int cnt = 0;
                for(int i = viz[x][y]; i < (int)states.size(); i++) {
                    cnt += (used[states[i].first] == false);
                    used[states[i].first] = true;
                }
                for(int i = viz[x][y]; i < (int)states.size(); i++) {
                    used[states[i].first] = false;
                }
                for(auto it:states) {
                    ans[it.first][it.second] = cnt;
                }
                break;
            }
            else {
                for(auto it:states) {
                    ans[it.first][it.second] = ans[x][y];
                }
                break;
            }
        }

        viz[x][y] = states.size();
        states.push_back({x,y});
    }
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&k[i]);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d",&sz[i]);

        for(int j = 1; j <= sz[i]; j++) {
            int x;
            scanf("%d",&x);
            graph[i].push_back(x);
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < LMAX; j++) {
            if(viz[i][j] == false) {
                solve(i,j);
            }
        }
    }

    int q;

    scanf("%d",&q);

    while(q--) {
        int u,v;
        scanf("%d %d",&u,&v);
        v = get_mod(v);
        printf("%d\n",ans[u][v]);
    }

    return 0;
}
