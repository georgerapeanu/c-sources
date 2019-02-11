#include <fstream>
#include <vector>
#include <algorithm>
#define mod 1000000007
using namespace std;

int tata[200010];
int g[200010];
vector <int> has[200010], doesnot[200010];
int nrbits = 30;
vector <int> adia[200010];
int val[200010];
vector <pair <int, int>> sorted;
int activated[200010];
int answered[200010];

int gaseste(int x)
{
    if (tata[x] != tata[tata[x]])
        tata[x] = gaseste(tata[x]);
    return tata[x];
}
void unite(int a, int b)
{
    a = gaseste(a);
    b = gaseste(b);

    if (g[a] < g[b])
        swap(a, b);

    for (int i(0); i < nrbits; i++) {
        int x = has[a][i], y = doesnot[a][i];
        int p = has[b][i], q = doesnot[b][i];
        has[a][i] = (x + p + 1ll * x * q + 1ll * p * y) % mod;
        doesnot[a][i] = (y + q + 1ll * x * p + 1ll * y * q) % mod;
    }
    g[a] += g[b];
    tata[b] = a;
}
int get_ans(int id, int val)
{
    int ans(0);
    for (int i(0); i < nrbits; i++) {
        if (val & (1 << i))
            ans = (ans + 1ll * (1ll << i) * doesnot[id][i]) % mod;
        else
            ans = (ans + 1ll * (1ll << i) * has[id][i]) % mod;
    }
    return ans;
}

int main()
{
    ifstream in("countfefete.in");
    ofstream out("countfefete.out");

    int n;
    in >> n;

    for (int i(1); i <= n; i++) {
        in >> val[i];
        sorted.push_back({ val[i], i });
        g[i] = 1;
        tata[i] = i;
        has[i] = vector <int> (nrbits, 0);
        doesnot[i] = vector <int> (nrbits, 0);
    }
    for (int i(1); i < n; i++) {
        int a, b;
        in >> a >> b;
        adia[a].push_back(b);
        adia[b].push_back(a);
    }

    sort(sorted.begin(), sorted.end());
    reverse(sorted.begin(), sorted.end());

    int ans(0);


    for (auto act : sorted) {

        int v = val[act.second], nr = act.second;
        activated[nr] = 1;

        for (auto i : adia[nr]) {
            if (activated[i]) {
                //ans = (ans + mod - get_ans(gaseste(i), 0)) % mod;
                ans = (ans + mod - get_ans(gaseste(i), v)) % mod;
                unite(nr, i);
            }
        }

        nr = gaseste(nr);

        int x = (get_ans(nr, 0) + get_ans(nr, v)) % mod;
        ans = (ans + x) % mod;

        /// il adaug pe v
        for (int i(0); i < nrbits; i++) {
            int x = has[nr][i], y = doesnot[nr][i];
            if (v & (1 << i)) {
                has[nr][i] = (x + y + 1) % mod;
                doesnot[nr][i] = (x + y) % mod;
            }
            else {
                has[nr][i] = 2 * x % mod;
                doesnot[nr][i] = (2 * y + 1) % mod;
            }
        }
    }

    out << ans << '\n';
    return 0;
}


