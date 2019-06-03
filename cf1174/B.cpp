#include <bits/stdc++.h>

using namespace std;

int n;
int v[int(1e5) + 4];

int main() {

    bool has_even = false;
    bool has_odd = false;

    cin >> n;

    for(int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        has_even |= (a % 2 == 0);
        has_odd |= (a % 2 == 1);
        v[i] = a;
    }

    if(has_even && has_odd) {
        sort(v + 1,v + 1 + n);
    }

    for(int i = 1; i <= n; i++) {
        printf("%d ",v[i]);
    }

    return 0;
}
