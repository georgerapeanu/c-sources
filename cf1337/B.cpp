#include <bits/stdc++.h>

using namespace std;

int t;
int n,m;

int main() {

    scanf("%d",&t);

    while(t--) {
        int x,n,m;

        scanf("%d %d %d",&x,&n,&m);

        bool ok = false;

        for(int i = 0; i <= n; i++) {
            if(x <= m * 10) {
                ok = true;
                break;
            }
            x = x / 2 + 10;
        }

        printf(ok ? "YES\n":"NO\n");
    }

    return 0;
}
