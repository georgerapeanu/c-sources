#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9 + 100, maxn = 1 << 20;

struct element {
    long long sum;
    int max, max2, nr;
};

element mk_element(int x) { return element{x, x, -inf, 1}; }

constexpr element zero{0, -inf, -inf, 0};

element operator+(element a, element b) {
    return a.max == b.max
               ? element{a.sum + b.sum, a.max, max(a.max2, b.max2), a.nr + b.nr}
           : a.max > b.max
               ? element{a.sum + b.sum, a.max, max(a.max2, b.max), a.nr}
               : element{a.sum + b.sum, b.max, max(a.max, b.max2), b.nr};
}

element operator*(int x, element a) {
    assert(x > a.max2);
    return element{a.sum - (long long)a.nr * max(a.max - x, 0), min(a.max, x),
                   a.max2, a.nr};
}

int lazy[maxn];
element buf[2 * maxn];

void apply(int i, int x) {
    if (i >= maxn)
        buf[i] = mk_element(min(buf[i].max, x));
    else if (x > buf[i].max2 && x < lazy[i]) {
        lazy[i] = x;
        buf[i] = x * buf[i];
    } else if (x <= buf[i].max2) {
        apply(2 * i, x);
        apply(2 * i + 1, x);
        lazy[i] = inf;
        buf[i] = buf[2 * i] + buf[2 * i + 1];
    }
}

void prop(int i) {
    if (i < maxn) {
        apply(2 * i, lazy[i]);
        apply(2 * i + 1, lazy[i]);
        lazy[i] = inf;
    }
}

void up(int x) {
    while (x /= 2) buf[x] = lazy[x] * (buf[2 * x] + buf[2 * x + 1]);
}

void down(int x) {
    for (int i = __builtin_ctz(maxn); i > 0; --i)
        if (x >> i) prop(x >> i);
}

element query(int st, int dr) {
    down(st += maxn);
    down((dr += maxn) - 1);

    element ret = zero;
    for (; st < dr; st /= 2, dr /= 2) {
        if (st % 2) ret = ret + buf[st++];
        if (dr % 2) ret = ret + buf[--dr];
    }

    return ret;
}

void update(int st, int dr, int x) {
    down(st += maxn);  // astea probabil pot fi sterse, vreau sa vad.
    down((dr += maxn) - 1);

    const int st0 = st, dr0 = dr;
    for (; st < dr; st /= 2, dr /= 2) {
        if (st % 2) apply(st++, x);
        if (dr % 2) apply(--dr, x);
    }

    up(st0);
    up(dr0 - 1);
}

int cbin(int st, int dr, int k) {
    auto t = query(st, dr);
    int k_ = t.nr - k, x = -1;

    auto upd = [&](int& k, int& k_, int i) {
        if (buf[i].max < t.max) return;
        if (k <= buf[i].nr) {
            x = i;
            k_ = buf[i].nr - k;
        } else
            k -= buf[i].nr;
    };

    for (st += maxn, dr += maxn; st < dr && x == -1; st /= 2, dr /= 2) {
        if (st % 2) upd(k, k_, st++);
        if (x == -1 && dr % 2) upd(k_, k, --dr);
    }

    while (x < maxn) {
        prop(x);
        x *= 2;
        if (buf[x].max < t.max)
            ++x;
        else if (buf[x].nr <= k)
            k -= buf[x++].nr;
    }

    if (k) ++x;

    return x - maxn;
}

void initialise(int n, int q, int h[]) {
    for (int i = 0; i < n; ++i) buf[i + maxn] = mk_element(h[i + 1]);
    for (int i = maxn - 1; i > 0; --i) {
        buf[i] = buf[2 * i] + buf[2 * i + 1];
        lazy[i] = inf;
    }
}

void cut(int l, int r, int k) {
    --l;
    while (k) {
        auto t = query(l, r);
        long long ops = (long long)(t.max - t.max2) * t.nr;
        if (ops <= k) {
            k -= ops;
            update(l, r, max(t.max2, 0));
        } else {
            int i = cbin(l, r, k % t.nr);
            update(l, i, max(t.max - k / t.nr - 1, 0));
            update(i, r, max(t.max - k / t.nr, 0));
            k = 0;
        }
    }
}

void magic(int i, int x) {
    down(i += maxn - 1);
    buf[i] = mk_element(x);
    up(i);
}

long long inspect(int l, int r) {
    auto t = query(l - 1, r);
    cerr << t.nr << '\r';
    return t.sum;
}

void fetchDebugData(int &count,int &max_count){
  count = -1;
  max_count = -1;
}
