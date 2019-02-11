#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
using namespace std;

typedef long long i64;

vector <pair <int, int>> v[100010];
vector <int> pozv;

inline int get_vector()
{
    int x = pozv.back();
    pozv.pop_back();
    return x;
}
inline void rem_vector(int x)
{
    v[x] = vector <pair <int, int>> ();
    pozv.push_back(x);
}

long long rez;
map <int, i64> mp[35];
int f;

void divide(vector <pair <int, int>> & act, int lvl)
{
    vector <pair <int, i64>> ans;
    if (act.empty())
        return;
    int bit = 0;
    if ((f - lvl - 2) >= 0)
        bit = (1 << (f - lvl - 2));
    int vst = get_vector(), vdr = get_vector();
    for (auto i : act) {
        if (i.second != lvl) {
            if (i.first & bit)
                v[vdr].push_back({ (i.first & (~bit)), i.second });
            else
                v[vst].push_back(i);
        }
        else {
            int x = i.first;
            ans.push_back({ i.first, 0 });
            for (int lev(lvl + 1), b = bit; lev < f; lev++, b /= 2) {
                x &= ~b;
                ans.back().second += mp[lev][x];
            }
            ans.back().second += (1 << (f - lvl - 1));

        }
    }
    divide(v[vst], lvl + 1);
    divide(v[vdr], lvl + 1);

    rem_vector(vst);
    rem_vector(vdr);

    for (auto & i : ans) {
        int x = i.first;
        for (int lev(lvl + 1), b = bit; lev < f; lev++, b /= 2) {
            x &= ~b;
            i.second -= mp[lev][x];
        }
        mp[lvl][i.first] += i.second;
        rez -= 1ll * i.second * (1 << lvl);
    }
}

int main()
{
    ifstream in("fft2d.in");
    ofstream out("fft2d.out");

    for (int i(0); i < 100000; i++)
        pozv.push_back(i);

    int t;
    in >> f >> t;

    rez = (1ll << (f - 1)) * (1ll << (f - 1));

    int vec = get_vector();

    while (t--) {
        int a, b;
        in >> a >> b;
        v[vec].push_back({ b, a });
    }

    divide(v[vec], 0);

    out << rez << '\n';
    return 0;
}
