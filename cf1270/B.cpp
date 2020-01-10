#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[int(2e5) + 5];

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d",&n);

        for(int i = 1; i <= n; i++) {
            scanf("%d",&a[i]);
        }

        int mi = 1e9,idx = -1;

        bool ok = false;

        for(int i = 1; i <= n; i++) {
            if(a[i] - i > mi) {
                printf("YES\n%d %d\n",idx,i);
                ok = true;
                break;
            }
            if(mi > a[i] - i) {
                mi = a[i] - i;
                idx = i;
            }
        }

        if(ok == false) {
            mi = 1e9;
            idx = -1;
            for(int i = n; i; i--) {
                if(a[i] - (n - i + 1) > mi) {
                    printf("YES\n%d %d\n",i,idx);
                    ok = true;
                    break;
                }
                if(mi > a[i] - (n - i + 1)) {
                    mi = a[i] - (n - i + 1);
                    idx = i;
                }
            }
        }

        if(ok == false) {
            printf("NO\n");
        }
    }

    return 0;
}
