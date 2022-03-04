#include <bits/stdc++.h>

#include "weirdtree.h"
using namespace std;

namespace {
constexpr int bufsz = 1 << 16;
char ibuf[bufsz], *ip, obuf[bufsz], *op = obuf;

void init() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin.read(ip = ibuf, bufsz);
}

void write() {
    cout.write(obuf, op - obuf);
    op = obuf;
}

void putch(char ch) {
    *op++ = ch;
    if (op == obuf + bufsz) {
        cout.write(op = obuf, bufsz);
    }
}

void putint(long long x) {
    if (x == 0)
        putch('0');
    else {
        static char buf[20], *p = buf;
        lldiv_t d;
        while (x) {
            d = lldiv(x, 10);
            *p++ = '0' + d.rem;
            x = d.quot;
        }
        while (p > buf) putch(*--p);
    }
}

void adv() {
    if (++ip == ibuf + bufsz) cin.read(ip = ibuf, bufsz);
}

int getint() {
    int x = 0;
    for (; *ip < '0'; adv())
        ;
    for (; *ip >= '0'; adv()) x = 10 * x + *ip - '0';
    return x;
}
}  // namespace

#ifdef TESTING

#define DEF_ENV(name) int env_##name = atoi(getenv(#name))

#endif

int main() {
#ifdef TESTING
    DEF_ENV(N);
    DEF_ENV(Q);
    DEF_ENV(k);
    DEF_ENV(magic);
    DEF_ENV(isfull);
#endif

    init();

    int n = getint();
    int q = getint();

#ifdef TESTING
    assert(1 <= n && n <= env_N);
    assert(1 <= q && q <= env_Q);
#endif

    int h[n + 1];
    for (int i = 1; i <= n; ++i) {
        h[i] = getint();
#ifdef TESTING
        assert(1 <= h[i] && h[i] <= 1e9);
#endif
    }
    initialise(n, q, h);

    int tmp_q = q;

    while (q--) {
        int t = getint();

        if (t == 1) {
            int l = getint(), r = getint(), k = getint();
#ifdef TESTING
            assert(!env_isfull || (1 == l && r == n));
            assert(1 <= l && l <= r && r <= n);
            assert(1 <= k && k <= 1e9);
#endif
            cut(l, r, k);
        } else if (t == 2) {
            int i = getint(), x = getint();
#ifdef TESTING
            assert(1 <= i && i <= n);
            assert(1 <= x && x <= 1e9);
#endif
            magic(i, x);
        } else {
            int l = getint(), r = getint();
#ifdef TETING
            assert(t == 3);
            assert(1 <= l && l <= r && r <= n);
            assert(!env_isfull || (1 == l && r == n));
#endif
            putint(inspect(l, r));
            putch('\n');
        }
    }

    write();
    return 0;
}
