#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e3;

int n,m;
long long v[2 * NMAX + 5][2 * NMAX + 5];

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            scanf("%lld",&v[i + j - 1][n - i + j]);
        }
    }

    for(int i = 1;i < n + m;i++){
        for(int j = 1;j < n + m;j++){
            v[i][j] += v[i - 1][j] + v[i][j - 1] - v[i - 1][j - 1];
        }
    }

    long long ans = -1e18;
    int ans_x = 1,ans_y = 1;

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            int r = min(min(i,n - i + 1),min(j,m - j + 1));

            int x = (i) + (j - r + 1) - 1;
            int y = n - (i) + (j - r + 1);
            
            int xx = (i) + (j + r - 1) - 1;
            int yy = n - (i) + (j + r - 1);

            long long sum = v[xx][yy] - v[x - 1][yy] - v[xx][y - 1] + v[x - 1][y - 1];

            if(sum > ans || (sum == ans && ans_x > i) || (sum == ans && ans_x == i && ans_y > j)){
                ans = sum;
                ans_x = i;
                ans_y = j;
            }
        }
    }

    printf("%d %d\n",ans_x,ans_y);

    return 0;
}
