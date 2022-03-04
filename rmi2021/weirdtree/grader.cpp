#include <iostream>

#include "weirdtree.h"
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;

    int h[N + 1];

    for (int i = 1; i <= N; ++i) cin >> h[i];

    initialise(N, Q, h);

    for (int i = 1; i <= Q; ++i) {
        int t;
        cin >> t;

        if (t == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            cut(l, r, k);
        } else if (t == 2) {
            int i, x;
            cin >> i >> x;
            magic(i, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << inspect(l, r) << '\n';
        }
    }
    return 0;
}
