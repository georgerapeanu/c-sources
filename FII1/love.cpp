#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;
const int VMAX = 1e6;

vector< pair<int,int> > graph[NMAX + 5];

int n;
long long dp[NMAX + 5][3];

void dfs(int nod,int tata) {
    long long min1 = 3LL* NMAX * VMAX;
    long long min2 = 3LL * NMAX * VMAX;
    long long sum = 0;
    for(auto xxx:graph[nod]) {
        int it = xxx.first;
        if(it != tata) {
            dfs(it,nod);
            long long val = max(max(dp[it][0],dp[it][1]),dp[it][2]) - max(dp[it][0],dp[it][1]) - xxx.second;
            sum += max(max(dp[it][0],dp[it][1]),dp[it][2]);
            if(val < min1) {
                min2 = min1;
                min1 = val;
            }
            else if(val < min2) {
                min2 = val;
            }
        }
    }

    dp[nod][0] = sum;

    if(min1 != 3LL * NMAX * VMAX) {
        dp[nod][1] = sum - min1;
    }
    else {
        dp[nod][1] = -3LL * NMAX * VMAX;
    }

    if(min2 != 3LL * NMAX * VMAX) {
        dp[nod][2] = sum - min1 - min2;
    }
    else {
        dp[nod][2] = -3LL * NMAX * VMAX;
    }

}

int main() {

    scanf("%d",&n);

    for(int i = 1; i < n; i++) {
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        graph[x].push_back({y,z});
        graph[y].push_back({x,z});
    }

    dfs(1,0);

    printf("%lld",max(dp[1][0],max(dp[1][1],dp[1][2])));

    return 0;
}
