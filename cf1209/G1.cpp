#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n,q;
int a[NMAX + 5];
int fst[NMAX + 5];
int lst[NMAX + 5];
int cnt[NMAX + 5];

int main() {

    scanf("%d %d",&n,&q);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        if(fst[a[i]] == 0) {
            fst[a[i]] = i;
        }
        lst[a[i]] = i;
        cnt[a[i]]++;
    }

    int l = 1,r = 1;
    set<int> s;
    int ans = 0;

    for(int i = 1; i <= n; i++) {
        if(r < i) {
            int ma = 0;
            for(auto it:s) {
                ma = max(ma,cnt[it]);
            }
            ans += (r - l + 1) - ma;
            s.clear();
            l = r = i;
        }
        r = max(r,lst[a[i]]);
        s.insert(a[i]);
    }

    int ma = 0;
    for(auto it:s) {
        ma = max(ma,cnt[it]);
    }
    ans += (r - l + 1) - ma;

    printf("%d\n",ans);

    return 0;
}
