#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
int v[NMAX + 5];

int last;

int main() {

    scanf("%d",&n);

    for(int i = 2; i <= n; i++) {
        if(v[i] != 0) {
            continue;
        }

        last++;

        for(int j = i; j <= n; j += i) {
            v[j] = last;
        }
    }

    for(int i = 2; i <= n; i++) {
        printf("%d ",v[i]);
    }

    return 0;
}
