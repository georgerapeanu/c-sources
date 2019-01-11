#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;
const int VMAX = 2e5;

vector<int> nodes_with_val[VMAX + 5];
vector<int> graph[NMAX + 5];

bool notprime[VMAX + 5];
bool active[NMAX + 5];
bool viz[NMAX + 5];

pair<int,int> dfs(int nod,int tata) {
    viz[nod] = true;
    pair<int,int> ans = {nod,1};

    for(auto it:graph[nod]) {
        if(it != tata && active[it]) {
            pair<int,int> tmp = dfs(it,nod);
            tmp.second++;
            ans = (ans.second < tmp.second ? tmp:ans);
        }
    }

    return ans;
}

int main() {

    int n;

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        nodes_with_val[val].push_back(i);
    }

    for(int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    notprime[0] = notprime[1] = true;

    int ans = 0;

    for(int i = 2; i <= VMAX; i++) {
        if(!notprime[i]) {
            for(int j = i; j <= VMAX; j += i) {
                notprime[j] = true;
                for(auto it:nodes_with_val[j]) {
                    viz[it] = false;
                    active[it] = true;
                }
            }

            for(int i = 1; i <= n; i++) {
                if(active[i] && !viz[i]) {
                    pair<int,int> a = dfs(i,0);
                    pair<int,int> b = dfs(a.first,0);
                    ans = max(ans,b.second);
                }
            }

            for(int j = i; j <= VMAX; j += i) {
                for(auto it:nodes_with_val[j]) {
                    viz[it] = false;
                    active[it] = false;
                }
            }
        }
    }

    printf("%d",ans);

    return 0;
}
