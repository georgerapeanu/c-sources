#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int ans = 0;
int n;
int v[NMAX + 5];
int sgn[NMAX + 5];

int main() {

    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    sort(v + 1,v + 1 + n);
    swap(v[1],v[n]);
    swap(v[2],v[n]);

    for(int i = 1; i <= n; i++) {
        if(i == 1) {
            ans += v[i];
            sgn[i] = 1;
        }
        else if(i == 2) {
            ans -= v[i];
            sgn[i] = - 1;
        }
        else {
            ans += (v[i] < 0 ? -v[i]:v[i]);
            sgn[i] = (v[i] < 0 ? -1:1);
        }
    }

    cout << ans << "\n";

    int fst = 1;
    int snd = 2;

    for(int i = 1; i < n - 1; i++) {
        if(sgn[snd + 1] == 1) {
            cout << v[snd] << " " << v[snd + 1] << "\n";
            v[snd + 1] = v[snd] - v[snd + 1];
            snd++;
        }
        else {
            cout << v[fst] << " " << v[snd] << "\n";
            v[snd] = v[fst] - v[snd];
            fst = snd;
            snd++;
        }
    }

    cout << v[fst] << " " << v[snd] << "\n";

    v[fst] -= v[snd];

    cerr << v[fst] << "\n";
    return 0;
}
