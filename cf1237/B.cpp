#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
int a[NMAX + 5];
int inv_a[NMAX + 5];
int b[NMAX + 5];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d",&b[i]);
    }

    reverse(a + 1,a + 1 + n);
    reverse(b + 1,b + 1 + n);

    for(int i = 1; i <= n; i++) {
        inv_a[a[i]] = i;
    }

    int largest_car = 0;
    int ans = 0;

    for(int i = 1; i <= n; i++) {
        if(largest_car > inv_a[b[i]]) {
            ans++;
        }
        largest_car = max(largest_car,inv_a[b[i]]);
    }

    printf("%d\n",ans);

    return 0;
}
