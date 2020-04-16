#include <bits/stdc++.h>

using namespace std;

int n;
int a[200005];
long long pref[200005];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        pref[i] = a[i] + pref[i - 1];
    }

    int lst = 0;

    map<long long,int> last;

    last[0] = 0;

    long long ans = 0;

    for(int i = 1; i <= n; i++) {
        if(last.count(pref[i])) {
            lst = max(lst,last[pref[i]] + 1);
        }
        ans += i - lst;
        last[pref[i]] = i;
    }

    printf("%lld\n",ans);

    return 0;
}
