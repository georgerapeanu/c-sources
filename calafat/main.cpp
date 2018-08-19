#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

ifstream f("calafat.in");
ofstream g("calafat.out");

const int Nmax = 200000;
const int Qmax = 200000;

const int Q = Qmax + 10;
const int N = Nmax + 10;

vector<pair<int, int> > qr[N];
pair<int, int> upd[N];
long long sol[Q], A[N];
int last[N], n, q, l, r, x;

void update(int p, int x) {
    for(; p <= n; p += p & -p) {
        A[p] += x;
    }
}

long long find(int p) {
    long long sum = 0;
    for (; p; p -= p & -p) {
        sum += A[p];
    }
    return sum;
}

int main () {
    f >> n >> q;
    assert(n >= 1 && n <= Nmax);
    assert(q >= 1 && q <= Qmax);
    for (int i = 1; i <= n; ++i) {
        f >> x;
        assert(x >= 1 && x <= Nmax);
        if (!last[x]) {
            last[x] = i;
        } else {
            upd[i] = make_pair(last[x], i - last[x]);
            last[x] = i;
        }
    }
    for (int i = 1; i <= q; ++i) {
        f >> l >> r;
        assert(l <= r && 1 <= l && l <= n && 1 <= r && r <= n);
        qr[r].push_back(make_pair(l, i));
    }
    for (int i = 1; i <= n; ++i) {
        if (upd[i].first) {
            update(upd[i].first, upd[i].second);
        }
        for (auto &it : qr[i]) {
            sol[it.second] = find(i) - find(it.first - 1);
        }
    }
    for (int i = 1; i <= q; ++i) {
        g << sol[i] << "\n";
    }
    return 0;
}
