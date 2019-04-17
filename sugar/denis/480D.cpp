#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 500;
const int SMAX = 1000;

struct box_t {
    int in;
    int out;
    int w,s;
    int v;
};

int n,s;
box_t v[NMAX + 5];

int dp[NMAX + 5][SMAX + 5];
int mem[NMAX + 5][2 * NMAX + 5];

vector<int> segm_end[2 * NMAX + 5];

int get_dp(int i,int s) {
    if(s < 0) {
        return -1e9;
    }

    if(dp[i][s] != -1) {
        return dp[i][s];
    }

    for(int t = v[i].in; t <= v[i].out; t++) {
        if(t > 0) {
            mem[i][t] = mem[i][t - 1];
        }
        else {
            mem[i][t] = 0;
        }
        for(auto it:segm_end[t]) {
            if(v[it].in < v[i].in) {
                continue;;
            }
            if(it == i) {
                continue;
            }
            mem[i][t] = max(mem[i][t],mem[i][v[it].in] + get_dp(it,min(s - v[it].w,v[it].s)));
        }
    }

    return dp[i][s] = (mem[i][v[i].out] + v[i].v);
}

int main() {

    scanf("%d %d",&n,&s);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d %d %d %d",&v[i].in,&v[i].out,&v[i].w,&v[i].s,&v[i].v);
        segm_end[v[i].out].push_back(i);
    }

    v[0] = {0,2 * n,0,s,0};

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= s; j++) {
            dp[i][j] = -1;
        }
    }

    printf("%d\n",get_dp(0,s));

    return 0;
}
