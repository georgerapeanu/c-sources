#include <bits/stdc++.h>

using namespace std;

int t;

int main() {

    int n,m;

    scanf("%d",&t);
    while(t--) {
        scanf("%d %d",&n,&m);
        int x = min(n - m, m - 1);
        printf("%d\n",min(n - 1,n - x - 1));
    }


    return 0;
}
