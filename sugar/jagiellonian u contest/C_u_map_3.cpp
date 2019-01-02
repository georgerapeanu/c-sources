#include <cstdio>
#include <unordered_map>
#include <algorithm>

using namespace std;

const int VMAX = 2e6;

unordered_map<int,int> aib[VMAX + 5];

int n;
int x[200005];
int y[200005];

void u(int x,int y,int val) {
    for(int i = x; i <= VMAX; i += i & (-i)) {
        for(int j = y; j <= VMAX; j += j & (-j)) {
            aib[i][j] = max(aib[i][j],val);
        }
    }
}

int q(int x,int y) {
    int ans = 0;
    for(int i = x; i; i -= (-i) & i) {
        for(int j = y; j; j -= (-j) & j) {
            ans = max(ans,aib[i][j]);
        }
    }
    return ans;
}

int main() {
    int t;

    scanf("%d",&t);

    while(t--) {
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
            int val = 1 + q(x[i] - 1,y[i] - 1);
            u(x[i],y[i],val);
            ans = max(ans,val);
        }

        printf("%d\n",ans);

        for(int i = 0; i <= VMAX; i++) {
            aib[i].clear();
        }
    }
    return 0;
}