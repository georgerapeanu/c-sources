#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int v[5005];
int dp[5005][5005];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
    }

    int l = 0;

    for(int i = 1; i <= n; i++) {
        if(v[i] != v[l]) {
            l++;
            v[l] = v[i];
        }
    }

    n = l;

    for(int l = 1; l < n; l++) {
        for(int i = 1; i <= n - l; i++) {
            int j = i + l;
            if(v[i] == v[j]) {
                dp[i][j] = 1 + dp[i + 1][j - 1];
            }
            else {
                dp[i][j] = 1 + min(dp[i + 1][j],dp[i][j - 1]);
            }
        }
    }

    printf("%d",dp[1][n]);

    return 0;
}
