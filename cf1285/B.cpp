#include <bits/stdc++.h>

using namespace std;

int t;
int n;
long long v[100005];

int main() {

    cin >> t;

    while(t--) {
        cin >> n;
        long long mi = 0;
        long long bst_ans = -1e18;
        for(int i = 1; i <= n; i++) {
            cin >> v[i];
            v[i] = v[i - 1] + v[i];
            if(i < n) {
                bst_ans = max(bst_ans,v[i] - mi);
                mi = min(mi,v[i]);
            }
        }
        for(int i = 1; i < n; i++) {
            bst_ans = max(bst_ans,v[n] - v[i]);
        }
        printf(bst_ans < v[n] ? "YES\n":"NO\n");
    }

    return 0;
}
