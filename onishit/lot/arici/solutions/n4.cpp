#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
template<class T> void check_min(T &a, const T &b){ a = (a < b) ? a : b; }
template<class T> void check_max(T &a, const T &b){ a = (a > b) ? a : b; }
#define all(x) (x).begin(), (x).end()

const int N = 1e2 + 3;

int n;
array<int, 3> a[N];
bool dp[N][N][N][N];
int val[N][N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        val[a[i][0]][a[i][1]] = a[i][2];
    }

    dp[1][0][0][0] = 1;
    dp[0][1][0][0] = 1;
    for(int x = 1; x <= n + 1; ++x){
        for(int y = 1; y <= n + 1; ++y){
            for(int sum = 0; sum <= n; ++sum){
                for(int apples = 0; apples <= n; ++apples){
                    if(dp[x - 1][y][sum][apples] || dp[x][y - 1][sum][apples]){
                        if(!val[x][y])
                            dp[x][y][sum][apples] = true;
                        else{
                            dp[x][y][sum + 1][apples + val[x][y] - 1] = true;
                        }
                    }
                }
            }
        }
    }

    for(int i = n; i >= 0; --i){
        int ans = n + 1;
        for(int j = 0; j <= n; ++j)
            if(dp[n + 1][n + 1][i][j])
                check_min(ans, abs(j - (i - j)));
        if(ans != n + 1){
            cout << i << " " << ans << "\n";
            break;
        }
    }
}
