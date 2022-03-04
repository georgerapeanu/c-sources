#include <bits/stdc++.h>
using namespace std;

#define DEF_ENV(name) int env_##name = atoi(getenv(#name))

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    DEF_ENV(N);
    DEF_ENV(Q);
    DEF_ENV(k);
    DEF_ENV(magic);
    DEF_ENV(testid);
    DEF_ENV(isfull);

    mt19937 mt(env_testid + 553322);

    int N = uniform_int_distribution<int>(0.9 * env_N, env_N)(mt);
    cout << N << ' ' << env_Q << endl;

    vector<int> init_vals(N);

    for (auto& x : init_vals) x = uniform_int_distribution<int>(1, 1e9)(mt);

    for (int i = 0; i < N; ++i)
        cout << uniform_int_distribution<int>(i < N / 4 ? 1e9 - 1e6 : 1,
                                              1e9)(mt)
             << ' ';

    cout << endl;

    int poz = uniform_int_distribution<int>(10, N - 10)(mt),
        when = uniform_int_distribution<int>(0, env_Q - 3)(mt);

    for (int i = 0; i < env_Q; ++i) {
        if ((i == when || i == when + 1) && env_k > 1) {
            cout << 1 << ' ' << poz << ' ' << poz << ' ' << 1e9 << endl;
            continue;
        }

        if (i == when + 2 && env_k > 1) {
            cout << 3 << ' ' << poz - 5 << ' ' << poz + 5 << endl;
            continue;
        }

        int t;
        do t = uniform_int_distribution<int>(1, 3)(mt);
        while (!env_magic && t == 2);

        int l = env_isfull ? 1 : uniform_int_distribution<int>(1, N)(mt),
            r = env_isfull ? N : uniform_int_distribution<int>(1, N)(mt),
            p = uniform_int_distribution<int>(1, N)(mt),
            x = uniform_int_distribution<int>(1, 1e9)(mt),
            k = uniform_int_distribution<int>(1, env_k)(mt);
        if (l > r) swap(l, r);

        if (t == 1)
            cout << 1 << ' ' << l << ' ' << r << ' ' << k << endl;
        else if (t == 2)
            cout << 2 << ' ' << p << ' ' << x << endl;
        else if (t == 3)
            cout << 3 << ' ' << l << ' ' << r << endl;
    }

    return 0;
}
