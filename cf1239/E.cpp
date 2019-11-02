#include <bits/stdc++.h>

using namespace std;

int n;
int a[55];

bitset<25 * 50000 + 5> dp[55][30];

int main() {

    scanf("%d",&n);

    int sum = 0;

    for(int i = 1; i <= 2 * n; i++) {
        scanf("%d",&a[i]);
        sum += a[i];
    }

    sort(a + 1,a + 1 + 2 * n);
    sum -= a[1];
    sum -= a[2];

    dp[2][1][0] = 1;

    for(int i = 3; i <= 2 * n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            if(j) {
                dp[i][j] |= (dp[i - 1][j - 1] << a[i]);
            }
        }
    }

    int bst = 0;

    for(int h = 0; h <= sum; h++) {
        if(dp[2 * n][n][h] && max(sum - h,h) < max(sum - bst,bst)) {
            bst = h;
        }
    }

    vector<int> v1 = {a[1]};
    vector<int> v2 = {a[2]};

    int x = 2 * n;
    int y = n;

    while(x > 2) {
        if(dp[x - 1][y][bst]) {
            v2.push_back(a[x]);
        }
        else {
            v1.push_back(a[x]);
            bst -= a[x];
            y--;
        }
        x--;
    }

    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    reverse(v2.begin(),v2.end());

    for(auto it:v1)printf("%d ",it);
    printf("\n");
    for(auto it:v2)printf("%d ",it);
    printf("\n");

    return 0;
}
