#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n,m;
vector<int> graph[NMAX + 5];
int val[NMAX + 5];
bool viz[NMAX + 5];

int dfs(int nod) {
    viz[nod] = 1;
    int ans = nod;
    for(auto it:graph[nod]) {
        if(!viz[it]) {
            int tmp = dfs(it);
            if(val[tmp] < val[ans]) {
                ans = tmp;
            }
        }
    }
    return ans;
}

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 0; i < n; i++) {
        scanf("%d",&val[i]);
    }

    for(int i = 0; i < m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    if(2 * (n - m - 1) > n) {
        printf("Impossible");
        return 0;
    }

    if(m == n - 1) {
        printf("0");
        return 0;
    }

    long long ans = 0;

    for(int i = 0; i < n; i++) {
        if(!viz[i]) {
            int tmp = dfs(i);
            ans += val[tmp];
            val[tmp] = 1 << 30;
        }
    }

    sort(val,val + n);

    for(int i = 0; i < n - m - 2; i++) {
        ans += val[i];
    }

    printf("%lld",ans);

    return 0;
}