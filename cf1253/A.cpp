#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[100005];

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d",&n);
        for(int i = 1; i <= n; i++) {
            int val;
            scanf("%d",&val);
            a[i] = val;
        }
        for(int i = 1; i <= n; i++) {
            int val;
            scanf("%d",&val);
            a[i] -= val;
        }
        int l = 1,r = n;

        while(l <= n && a[l] == 0) {
            l++;
        }

        while(r > 0 && a[r] == 0) {
            r--;
        }

        bool ok = (l > n || a[l] <= 0);

        for(int i = l + 1; i <= r; i++) {
            ok &= (a[i] == a[i - 1]);
        }

        printf(ok ? "YES\n" : "NO\n");
    }

    return 0;
}
