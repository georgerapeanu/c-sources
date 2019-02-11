#include <fstream>
#include <vector>
#include <algorithm>
#define mod 1000000007
using namespace std;

int put(int x, int p)
{
    int ans(1);
    while (p) {
        if (p & 1)
            ans = 1ll * ans * x % mod;
        x = 1ll * x * x % mod;
        p /= 2;
    }
    return ans;
}

int inc(vector <int> v, int s, int lvl)
{
    int where(-1);
    for (int i(0); i < v.size() - 1; i++) {
        if ((v[i] + 1) % s != v[i + 1])
            where = (i + 1) % s;
    }
    if (where != -1) {
        for (int i(0); i < v.size() - 1; i++) {
            if ((i + 1) % s != where && (v[i] + 1) % s != v[i + 1])
                return -1;
        }
    }
    if (where == -1) {
        for (int i(0); i < v.size(); i++) {
            if (v[i] == 0) {
                int inceput = (i == 0 ? 0 : (v.back() + 1) % s);
                return (1ll * inceput * put(s, lvl + 1) -
                        1ll * (inceput - v[0]) * put(s, lvl)) % mod;
            }
        }
        return 1ll * ((v.back() + 1) % s) * put(s, lvl + 1) % mod;
    }
    vector <int> recurs;
    int last(0), beg(-1);
    for (int i(0); i < v.size(); i++) {
        if ((i + 1) % s == where) {
            /// tai aici
            if (beg == -1)
                beg = (s - i - 1);
            recurs.push_back((v[i] + 1) % s);
            if (i + 1 < v.size())
                last = v[i + 1];
            else
                last = -1;
        }
    }
    if (last != -1)
        recurs.push_back(last);

    int x = inc(recurs, s, lvl + 1);
    if (x == -1)
        return -1;

    x = (x + 1ll * beg * put(s, lvl)) % mod;

    return x;
}

int main()
{
    ifstream in("pscfft.in");
    ofstream out("pscfft.out");

    int t;
    in >> t;

    while (t--) {
        int n, s;
        in >> n >> s;
        vector <int> v(n);
        for (auto & i : v)
            in >> i;
        out << inc(v, s, 0) << '\n';
    }

    return 0;
}






