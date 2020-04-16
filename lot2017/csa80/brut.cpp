#include <bits/stdc++.h>

using namespace std;

int n;
int coef[100];
int v[100];

int main() {

    cin >> n;

    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    int ans = 0;

    for(int i = 1; i <= n; i++) {
        vector<int> active;
        for(int j = i; j <= n; j++) {
            active.push_back(v[j]);
            sort(active.begin(),active.end());
            active.resize(unique(active.begin(),active.end()) - active.begin());
            for(int i = 0; i < (int)active.size(); i++) {
                coef[active[i]] += i + 1;
                ans += (i + 1) * active[i];
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        cout << i << " " << coef[i] * i << "\n";
        ans -= coef[i] * i;
    }

    cout << ans;

    return 0;
}
