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
} in("fft2d.in");
ofstream out("fft2d.out");

const int DIM = 100005;
const int EXP = 35;

pair<int, int> arr[DIM];
vector<int> edg[DIM], teg[DIM]; bitset<DIM> oki;

int rnk[DIM], str[DIM]; long long dp[DIM];

int _sz;
void dfs(int x) {
    oki[x] = true;
    for (int i = 0; i < edg[x].size(); ++i)
        if (!oki[edg[x][i]])
            dfs(edg[x][i]);
    str[++_sz] = x;
}

int _f;
long long calcDp(int x) {
    if (dp[x] >= 0)
        return dp[x];
    dp[x] = (1LL << arr[x].first) * (1LL << (_f - arr[x].first));

    for (int i = 0; i < teg[x].size(); ++i) {
        int y = teg[x][i];

        calcDp(y);
        dp[x] -= (1LL << arr[x].first) * (1LL << (_f - arr[y].first));
    }

    return dp[x];
}

int main(void) {
    int f, n;
    in >> f >> n; f--; _f = f;

    for (int i = 1; i <= n; ++i)
        in >> arr[i].first >> arr[i].second, dp[i] = -1;
    sort(arr + 1, arr + n + 1);

    for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j) {
        if (arr[i].first == arr[j].first)
            continue;

        bool ok = true;
        int l1 = f - arr[i].first,
            l2 = f - arr[j].first;

        for (int k = 0; k < f && ok; ++k)
            if ((k >= l1 || k < l2) &&
                ((arr[i].second >> k) & 1) != ((arr[j].second >> k) & 1))
            ok = false;

        if (ok)
            edg[i].push_back(j), rnk[j]++;
    }

    for (int i = 1; i <= n; ++i)
        if (!rnk[i]) dfs(i);

    oki.reset();
    for (int i = 1; i <= n; ++i) {
        oki[str[i]] = true;

        for (int j = 0; j < edg[str[i]].size(); ++j)
            if (oki[edg[str[i]][j]])
                teg[str[i]].push_back(edg[str[i]][j]),
                oki[edg[str[i]][j]] = false;
    }

    oki.reset();

    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += calcDp(i);

    out << (1LL << f) * (1LL << f) - ans << "\n";

    return 0;
}
