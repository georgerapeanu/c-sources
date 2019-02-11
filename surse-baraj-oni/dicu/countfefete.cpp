#include <fstream>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;

class InputReader {
private:
    FILE *inFile;
    static const int SIZE = 1 << 17;
    char buf[SIZE]; int ptx;

    inline void advance(void) {
        if (++ptx == SIZE) {
            ptx = 0;
            fread(buf, SIZE, 1, inFile);
        }
    }
public:
    InputReader(const char *fileName) {
        inFile = fopen(fileName, "r");
        ptx = 0; fread(buf, SIZE, 1, inFile);
    }

    InputReader &operator >>(int &val) {
        val = 0;

        while (buf[ptx] < '0' || buf[ptx] > '9')
            advance();

        while (buf[ptx] >= '0' && buf[ptx] <= '9') {
            val = val * 10 + (buf[ptx] - '0');
            advance();
        }

        return *this;
    }
} in("countfefete.in");
ofstream out("countfefete.out");

const int DIM = 200005;
const int MOD = 1000000007;

struct str {
    int anc;
    int num[31][2];

    str() {
        this -> anc = -1;
        for (int i = 0; i < 31; ++i)
            this -> num[i][0] = this -> num[i][1] = 0;
    }
} pmd[DIM];

int ans = 0;
int val[DIM], evn[DIM];

bitset<DIM> oki;
vector<int> edg[DIM];

inline bool cmp(int x, int y) {
    return val[x] > val[y];
}

inline int getAnc(int x) {
    while (pmd[x].anc > 0)
        x = pmd[x].anc;
    return x;
}

void unite(int x, int y, int val) {
    x = getAnc(x); y = getAnc(y);

    if (pmd[x].anc > pmd[y].anc)
        swap(x, y);

    int aux[2];
    for (int i = 0; i < 31; ++i) {
        aux[0] = aux[1] = 0;

        for (int b0 = 0; b0 <= 1; ++b0)
        for (int b1 = 0; b1 <= 1; ++b1) {
            if (b0 ^ b1 ^ ((val >> i) & 1))
                ans = ((1LL << i) * pmd[x].num[i][b0] % MOD *
                                    pmd[y].num[i][b1] % MOD + ans) % MOD;

            aux[b0 ^ b1] = (1LL* pmd[x].num[i][b0] *
                                 pmd[y].num[i][b1] % MOD + aux[b0 ^ b1]) % MOD;
        }

        pmd[x].num[i][0] = (0LL + pmd[x].num[i][0] + pmd[y].num[i][0] + aux[0]) % MOD;
        pmd[x].num[i][1] = (0LL + pmd[x].num[i][1] + pmd[y].num[i][1] + aux[1]) % MOD;
    }

    pmd[x].anc += pmd[y].anc;
    pmd[y].anc = x;
}

int main(void) {
    int n;
    in >> n;

    for (int i = 1; i <= n; ++i) {
        in >> val[i];
        evn[i] = i;

        for (int j = 0; j < 31; ++j)
            pmd[i].num[j][(val[i] >> j) & 1] = 1;
    }

    for (int i = 1; i < n; ++i) {
        int x, y;
        in >> x >> y;

        edg[x].push_back(y);
        edg[y].push_back(x);
    }

    sort(evn + 1, evn + n + 1, cmp);

    for (int i = 1; i <= n; ++i) {
        int x = evn[i], pos = -1; oki[x] = true;

        for (int j = 0; j < edg[x].size(); ++j) {
            int y = edg[x][j];
            if (!oki[y])
                continue;

            if (pos == -1)
                pos = y;
            else
                unite(pos, y, val[x]);
        }

        if (pos != -1)
            unite(pos, x, val[x]);
    }

    out << ans << "\n";
    return 0;
}
