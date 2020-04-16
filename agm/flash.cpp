#include <bits/stdc++.h>

using namespace std;

int get_cnt(int n,int sum) {
    if(sum <= n + 1) {
        return sum - 1;
    }
    else {
        return n - (sum - n) + 1;
    }
}

int main() {

    int n;

    scanf("%d",&n);

    long long ans = 0;

    for(int i = 1; 1LL * i * i + 2 <= n + n; i++) {
        ans += get_cnt(n,i * i + 2);
    }

    printf("%lld\n",ans);

    return 0;
}
