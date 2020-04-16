#include <bits/stdc++.h>

using namespace std;

int t;
int col[1005];
int v[1005];

int main() {

    for(int h = 2; h <= 1000; h++) {
        if(col[h] == 0) {
            for(int x = h; x <= 1000; x += h) {
                if(col[x] == 0) {
                    col[x] = h;
                }
            }
        }
    }

    scanf("%d",&t);

    while(t--) {
        int n;
        scanf("%d",&n);

        map<int,int> to_norm;
        for(int i = 1; i <= n; i++) {
            scanf("%d",&v[i]);
            v[i] = col[v[i]];
            to_norm[v[i]] = 1;
        }

        int lst = 0;

        for(auto &it:to_norm) {
            it.second = ++lst;
        }

        printf("%d\n",lst);

        for(int i = 1; i <= n; i++) {
            printf("%d ",to_norm[v[i]]);
        }

        printf("\n");
    }

    return 0;
}
