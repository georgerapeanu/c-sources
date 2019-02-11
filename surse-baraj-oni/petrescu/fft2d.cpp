#include <cstdio>
#include <algorithm>

FILE *fin = fopen("fft2d.in", "r"), *fout = fopen("fft2d.out", "w");

#define MAXN 6000000
#define MAXT 100000

struct node {
    int sum, st, dr;
} trie[MAXN];
int f, root[31], n;
int left, right, val, poz;
int ret[MAXT];

struct myc {
    int h, p;
    inline bool operator < (const myc &u) const {
        return h > u.h;
    }
} v[MAXT];

int update(int p, int h) {
    if (p == 0)
        p = ++n;
    trie[p].sum += val;
    if (h) {
        if (poz & (1 << h))
            trie[p].dr = update(trie[p].dr, h - 1);
        else
            trie[p].st = update(trie[p].st, h - 1);
    }
    return p;
}

inline int getAdev(int x, int y) {
    int z = x & ((1 << y) - 1);
    x >>= y;
    x += z << (f - y - 1);
    return x;
}

inline void interogare(int h, int p, int cat) {
    p = getAdev(p, h);
    int q = root[h], l = f - 1;
    while (q && l >= cat) {
        if (p & (1 << l))
            q = trie[q].dr;
        else
            q = trie[q].st;
        l--;
    }
    val -= trie[q].sum;
}

int main() {
    int t;
    fscanf(fin, "%d%d", &f, &t);

    for (int i = 0; i < t; i++)
        fscanf(fin, "%d%d", &v[i].h, &v[i].p);

    std::sort(v, v + t);

    long long ans = 1LL << (2 * f - 2);
    for (int p = 0; p < t; p++) {
        val = 1 << (f - v[p].h - 1);
        for (int k = f - 1; k > v[p].h; k--)
            interogare(f - k - 1, v[p].p, k - v[p].h);
        ans -= val << v[p].h;
        poz = getAdev(v[p].p, f - v[p].h - 1);
        root[f - v[p].h - 1] = update(root[f - v[p].h - 1], f - 1);
    }

    fprintf(fout, "%lld\n", ans);

    fclose(fin);
    fclose(fout);
    return 0;
}
