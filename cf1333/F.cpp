#include <bits/stdc++.h>

using namespace std;

int n;
int dp[500005];
int ciur[500005];

int main() {

    scanf("%d",&n);

    int active = 0;

    for(int i = n; i; i--) {
        dp[i] = i + active;

        active++;

        for(int j = i; j <= n; j += i) {
            ciur[j]++;
            if(ciur[j] == 2) {
                active--;
            }
        }
    }

    int lst = 2;

    for(int i = 1; i <= n; i++) {
        while(lst <= dp[i]) {
            printf("%d ",i);
            lst++;
        }
    }

    return 0;
}
