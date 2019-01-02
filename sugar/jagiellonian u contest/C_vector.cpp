#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int VMAX = 2e6;

int n;
int x[200005];
int y[200005];

class AIB {

    vector<int> tree[VMAX + 5];
    vector<int> vals[VMAX + 5];
    vector<int> active_rows;

public:

    void preup(int x,int y) {
        for(int i = x; i <= VMAX; i += (-i) & i) {
            for(int j = y; j <= VMAX; j += (-j) & j) {
                vals[i].push_back(j);
            }
            active_rows.push_back(i);
        }
    }

    void create() {
        sort(active_rows.begin(),active_rows.end());
        active_rows.resize(unique(active_rows.begin(),active_rows.end()) - active_rows.begin());

        for(auto it:active_rows) {
            sort(vals[it].begin(),vals[it].end());
            vals[it].resize(unique(vals[it].begin(),vals[it].end()) - vals[it].begin());
            tree[it].resize(vals[it].size() + 1);
        }
    }

    void reset() {
        for(auto it:active_rows) {
            tree[it].clear();
            vals[it].clear();
        }
        active_rows.clear();
    }

    void update(int x,int y,int val) {
        for(int i = x; i <= VMAX; i += (-i) & i) {
            int z = lower_bound(vals[i].begin(),vals[i].end(),y) - vals[i].begin() + 1;
            for(int j = z; j < (int)tree[i].size(); j += (-j) & j) {
                tree[i][j] = max(tree[i][j],val);
            }
        }
    }

    int query(int x,int y) {
        int ans = 0;
        for(int i = x; i; i -= (-i) & i) {
            int z = lower_bound(vals[i].begin(),vals[i].end(),y) - vals[i].begin();
            for(int j = z; j; j -= (-j) & j) {
                ans = max(ans,tree[i][j]);
            }
        }

        return ans;
    }
};

AIB aib;

int main() {
    int t;

    scanf("%d",&t);

    while(t--) {
        aib.reset();
        int n;

        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            scanf("%d",&x[i]);
        }

        for(int i = 1; i <= n; i++) {
            scanf("%d",&y[i]);
        }

        int ans = 0;

        for(int i = 1; i <= n; i++) {
            aib.preup(x[i],y[i]);
        }

        aib.create();

        for(int i = 1; i <= n; i++) {
            int val = 1 + aib.query(x[i] - 1,y[i] - 1);
            aib.update(x[i],y[i],val);
            ans = max(ans,val);
        }
        printf("%d\n",ans);
    }
    return 0;
}