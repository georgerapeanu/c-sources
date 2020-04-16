#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int a[100005];
int b[100005];
int fstn,fstp;

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d",&n);

        fstn = -1;
        fstp = -1;

        for(int i = 1; i <= n; i++) {
            scanf("%d",&a[i]);
            if(a[i] < 0) {
                if(fstn == -1) {
                    fstn = i;
                }
            }
            else if(a[i] > 0) {
                if(fstp == -1) {
                    fstp = i;
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            scanf("%d",&b[i]);
        }

        bool ok = true;

        for(int i = n; i; i--) {
            if(a[i] - b[i] < 0) {
                ok &= (fstp != -1 && fstp < i);
            }
            if(a[i] - b[i] > 0) {
                ok &= (fstn != -1 && fstn < i);
            }
        }

        printf(ok == true ? "YES\n":"NO\n");
    }

    return 0;
}
