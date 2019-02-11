#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct nod
{
    int h, x, popeala;
}; vector <nod> v, aux[35], a;
vector <int> sp;
int n, k; long long ans = 0;

nod trans(int h, int x)
{
    nod nou;
    nou.h = h;
    nou.x = x;
    nou.popeala = (1 << (n + 1)) - (1 << (h + 1));
    return nou;
}
int comp(nod x, nod y)
{
    int st, dr, hh, med, last = 0, v1, v2;
    hh = n - max(x.h, y.h), v1, v2;
    st = 1; dr = hh;
    while (st <= dr)
    {
        med = (st + dr) / 2;
        v1 = x.x % (1 << med);
        v2 = y.x % (1 << med);
        if (v1 == v2)
        {
            last = med;
            st = med + 1;
        }
        else
            dr = med - 1;
    }
    // primii last biti sunt egali
    if (last == hh)
        return 0; /// x == y;

    v1 = (1 << (last)) & x.x;
    if (v1 > 0)
        v1 = 1;

    v2 = (1 << (last)) & y.x;
    if (v2 > 0)
        v2 = 0;

    if (v1 > v2)
        return 1; /// x > y;
    else
        return -1; /// x < y;
    return 0;
}
bool cmp(nod aa, nod bb)
{
    int rez = comp(aa, bb);
    if (rez == 0)
        return aa.h < bb.h;
    else
        return rez < 0;
}
int bsleft(nod xx)
{
    int st, dr, med, last = -1, rez;
    st = 0; dr = v.size() - 1;
    while (st <= dr)
    {
        med = (st + dr) / 2;
        rez = comp(v[med], xx);
        if (rez == 0)
        {
            last = med;
            dr = med - 1;
        }
        else if (rez == 1)
            dr = med - 1;
        else
            st = med + 1;
    }
    return last;
}
int bsright(nod xx)
{
    int st, dr, med, last = -1, rez;
    st = 0; dr = v.size() - 1;
    while (st <= dr)
    {
        med = (st + dr) / 2;
        rez = comp(v[med], xx);
        if (rez == 0)
        {
            last = med;
            st = med + 1;
        }
        else if (rez == 1)
            dr = med - 1;
        else
            st = med + 1;
    }
    return last;
}
void solve(int niv)
{
    if (niv == n + 1 || v.size() == 0)
        return ;

    aux[niv].clear();
    sp.clear();
    a.clear();

    for (int i = 0; i < v.size(); ++i)
    {
        aux[niv].push_back(v[i]);
        if (v[i].h == niv)
            a.push_back(v[i]);
    }
    sp.push_back(v[0].popeala);
    for (int i = 1; i < v.size(); ++i)
        sp.push_back(sp[i - 1] + v[i];
    for (int i = 0; i < a.size(); ++i)
    {
        int st, dr;
        st = bsleft(a[i]);
        dr = bsright(a[i]);
    }
    v.clear();
    for (int i = 0; i < aux[niv].size(); ++i)
    {
        nod temp = aux[niv][i];
        if (aux[niv][i].h != niv && /** ceva **/ aux[niv][i].x / (1 << (n - niv - 1)) == 0)
            v.push_back(aux[niv][i]);
    }
    solve(niv + 1);
    v.clear();
    for (int i = 0; i < aux[niv].size(); ++i)
        if (aux[niv][i].h != niv && /** ceva **/ aux[niv][i].x / (1 << (n - niv - 1)) == 1)
            v.push_back(aux[niv][i]);
    solve(niv + 1);
}
int main()
{
    freopen("fft2d.in", "r", stdin);
    freopen("fft2d.out", "w", stdout);
    int h, x;
    scanf("%d %d", &n, &k); --n;
    for (int i = 1; i <= k; ++i)
    {
        scanf("%d %d\n", &h, &x);
        v.push_back(trans(h, x));
    }
    sort (v.begin(), v.end(), cmp);
    for (int i = 0; i < v.size(); ++i)
        printf("%d %d\n", v[i].h, v[i].x);
    solve(0);
    printf("%lld\n", 1LL * (1 << (n + n)) - ans);
    return 0;
}
