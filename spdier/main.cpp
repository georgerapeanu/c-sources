#include <cstdio>
#include <vector>
#include <algorithm>
#define infile "spider.in"
#define outfile "spider.out"
#define nMax 1013

using namespace std;

#define point pair <int, int>
point outside = make_pair(-1, -1);

const int ii[] = {-1, 0, 1, 0};
const int jj[] = {0, 1, 0, -1};

int best[nMax][nMax][5];
int h[nMax][nMax];
int n, m;

point sol;
int steps;

inline bool valid(point p) {
    if (p.first < 1 || p.first > n) return false;
    if (p.second < 1 || p.second > m) return false;
    return true;
}

inline int getHeight(point p) {

    if (p == outside) {
        return -1;
    }

    return h[p.first][p.second];
}

pair<point, int> getNextPosition(point crt, point prv) {

    point ret = outside;
    int dir = -1;

    for (int t = 0; t < 4; ++t) {
        point nxt = make_pair(crt.first + ii[t], crt.second + jj[t]);
        if (nxt != prv && valid(nxt) && getHeight(ret) < getHeight(nxt) && getHeight(nxt) <= getHeight(crt)) {
            ret = nxt;
            dir = t;
        }
    }

    return make_pair(ret, dir);
}

void read() {

    scanf("%d %d\n", &n, &m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &h[i+1][j+1]);
        }
    }
}

int solve(int x, int y, int d) {

    if (best[x][y][d]) {
        return best[x][y][d];
    }

    best[x][y][d] = 1;
    point prv;

    if (d == 4) {
        prv = outside;
    } else {
        prv = make_pair(x + ii[d], y + jj[d]);
    }

    pair<point, int> nxt = getNextPosition(make_pair(x, y), prv);

    if (nxt.first != outside) {
        best[x][y][d] += solve(nxt.first.first, nxt.first.second, (nxt.second + 2) % 4);
    }

    return best[x][y][d];
}

void solve() {

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
                int dist = solve(i+1, j+1, 4);
                if (dist > steps) {
                    steps = dist;
                    sol = make_pair(i+1, j+1);
                }
        }
    }

}

void write() {

    printf("%d\n", steps - 1);

    point prv = outside;

    while(sol != outside) {
        printf("%d %d\n", sol.first, sol.second);
        point aux = getNextPosition(sol, prv).first;

        prv = sol;
        sol = aux;
    }
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);

    read();
    solve();
    write();

    fclose(stdin);
    fclose(stdout);
    return 0;
}

