#include<bits/stdc++.h>

using namespace std;

int ans = 0, N, val[200009], p2[200009], t[200009], sz[200009], cnt[200009][32], aux[32];
const int mod = 1e9 + 7;
pair < int, int > a[200009];
vector < int > v[200009];

int add (int a, int b) {int c = a + b; if (c >= mod) c -= mod; return c;}
int subtract (int a, int b) {int c = a - b; if (c < 0) c += mod; return c;}
int mul (int x, int y) {return (1LL * x * y) % mod;}
void adto (int &a, int b) {a += b; if (a >= mod) a -= mod;}

int tata (int x)
{
    if (t[x] == x) return x;
    return t[x] = tata (t[x]);
}

void addNode (int nod)
{
    ///cnt contains the empty set (although it shouldn't matter as the empty set gives 0 xor)
    t[nod] = nod, sz[nod] = 1;
    for (int i=0; i<30; i++)
    {
        if (val[nod] & (1 << i)) cnt[nod][i] = 1;
        else cnt[nod][i] = 0;
        aux[i] = 0;
    }
    int overAllCount = 0;
    for (auto it : v[nod])
    if (t[it] != 0)
    {
        ///make the link
        int lin = tata (it);
        t[lin] = nod;
        ///alter data
        for (int i=0; i<30; i++)
        {
            ///subract those fully inside
            aux[i] = add (aux[i], cnt[lin][i]);
            ///merging data
            int a1 = cnt[nod][i], a0 = subtract (p2[sz[nod]], a1);
            int b1 = cnt[lin][i], b0 = subtract (p2[sz[lin]], b1);
            cnt[nod][i] = add (mul (a1, b0), mul (a0, b1));
        }
        overAllCount = subtract (overAllCount, p2[sz[lin]]), adto (overAllCount, 1);///the empty thing
        sz[nod] += sz[lin];
    }
    adto (overAllCount, subtract (p2[sz[nod]], 1));
    for (int i=0; i<30; i++)
    {
        int curr = subtract (cnt[nod][i], aux[i]);
        if (val[nod] & (1 << i)) curr = subtract (overAllCount, curr);
        adto (ans, mul (curr, 1 << i));
    }
}

int main ()
{
freopen ("countfefete.in", "r", stdin);
freopen ("countfefete.out", "w", stdout);

scanf ("%d", &N), p2[0] = 1;
for (int i=1; i<=N; i++)
    p2[i] = add (p2[i - 1], p2[i - 1]);
for (int i=1; i<=N; i++)
    scanf ("%d", &val[i]), a[i].second = i, a[i].first = val[i];
sort (a + 1, a + N + 1);
for (int i=1; i<N; i++)
{
    int x, y;
    scanf ("%d %d", &x, &y);
    v[x].push_back (y);
    v[y].push_back (x);
}
for (int i=N; i>=1; i--)
    addNode (a[i].second);
printf ("%d\n", ans);
return 0;
}
