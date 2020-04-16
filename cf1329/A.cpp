#include <bits/stdc++.h>

using namespace std;

int n,m;
int v[100005];
long long pref[100005];

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        scanf("%d",&v[i]);
        pref[i] = v[i] + pref[i - 1];
    }

    if(pref[m] < n) {
        printf("-1\n");
        return 0;
    }

    int fst = n + 1;

    for(int i = m; i; i--) {
        fst = min(fst - 1,n - v[i] + 1);
        if(fst < 1) {
            printf("-1");
            return 0;
        }
        if(pref[i - 1] < fst - 1 && pref[i - 1] + v[i] < fst) {
            printf("-1");
            return 0;
        }
        if(pref[i - 1] < fst - 1) {
            fst = pref[i - 1] + 1;
        }
        v[i] = fst;
    }

    for(int i = 1; i <= m; i++) {
        printf("%d ",v[i]);
    }



    return 0;
}
