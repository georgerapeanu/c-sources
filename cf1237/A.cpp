#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e4;

int n;
int a[NMAX + 5];
bool cnt = false;

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        if(a[i] % 2 != 0) {
            cnt ^= 1;
            if(cnt) {
                if(a[i] > 0) {
                    a[i] = a[i] / 2;
                }
                else {
                    a[i] = a[i] / 2 - 1;
                }
            }
            else {
                if(a[i] > 0) {
                    a[i] = a[i] / 2 + 1;
                }
                else {
                    a[i] = a[i] / 2;
                }
            }
        }
        else {
            a[i] = a[i] / 2;
        }
    }

    for(int i = 1; i <= n; i++)printf("%d\n",a[i]);

    return 0;
}
