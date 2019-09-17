#include <bits/stdc++.h>

using namespace std;

int n;
int a[105];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }

    sort(a + 1,a + 1 + n);

    int lst = 0;

    for(int i = 1; i <= n; i++) {
        bool ok = false;

        for(int j = 1; j <= lst; j++) {
            if(a[i] % a[j] == 0) {
                ok = true;
                break;
            }
        }

        if(ok == false) {
            a[++lst] = a[i];
        }
    }

    printf("%d\n",lst);

    return 0;
}
