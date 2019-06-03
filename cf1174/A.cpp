#include <bits/stdc++.h>

using namespace std;

int n;
int v[2005];

int main() {

    cin >> n;

    for(int i = 1; i <= 2 * n; i++) {
        cin >> v[i];
    }

    sort(v + 1,v + 1 + 2 * n);

    long long a = 0,b = 0;

    for(int i = 1; i <= n; i++)a += v[i];
    for(int i = n + 1; i <= 2 * n; i++)b += v[i];

    if(a == b)printf("-1");
    else for(int i = 1; i <= 2 * n; i++)printf("%d ",v[i]);

    return 0;
}
