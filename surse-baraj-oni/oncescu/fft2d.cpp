#include<bits/stdc++.h>

using namespace std;

int N, F;
long long dp0[100009], dp1[100009];
vector < pair < int, int > > v[35];

const int maxNodes = 3300000;
int trieRoot[35], nodes, nxt[maxNodes][2];
long long a[maxNodes], b[maxNodes];

void addPair (int &curr, long long &v0, long long &v1)
{
    a[curr] += v0;
    b[curr] += v1;
}

void add (int msk, int i, long long &v0, long long &v1)
{
    int curr = trieRoot[i];
    for (int k = 0; k < i; k ++)
    {
        addPair (curr, v0, v1);
        int bit = (msk >> k) & 1;
        if (nxt[curr][bit] == 0) nxt[curr][bit] = ++nodes;
        curr = nxt[curr][bit];
    }
    for (int k=F - 2; k>i; k--)
    {
        addPair (curr, v0, v1);
        int bit = (msk >> k) & 1;
        if (nxt[curr][bit] == 0) nxt[curr][bit] = ++nodes;
        curr = nxt[curr][bit];
    }
    addPair (curr, v0, v1);
}

void update (long long &v0, long long &v1, long long &x, long long &y)
{
    v0 += x;
    v1 += y;
}

void askAndUpdate (int msk, int i, int j, long long &v0, long long &v1)
{
    int curr = trieRoot[i];
    for (int k = 0; k < i; k ++)
    {
        int bit = (msk >> k) & 1;
        if (nxt[curr][bit] == 0) return ;
        curr = nxt[curr][bit];
    }
    for (int k=F - 2; k>=j; k--)
    {
        int bit = (msk >> k) & 1;
        if (nxt[curr][bit] == 0) return ;
        curr = nxt[curr][bit];
    }
    update (v0, v1, a[curr], b[curr]);
}

int main ()
{
freopen ("fft2d.in", "r", stdin);
freopen ("fft2d.out", "w", stdout);

scanf ("%d %d", &F, &N);
for (int i=1; i<=N; i++)
{
    int x, y;
    scanf ("%d %d", &x, &y);
    x = F - 1 - x;
    v[x].push_back ({y, i});
}
long long ans = 1LL << (F - 1);
ans = 1LL * ans * ans;
for (int lin = 0; lin <= F - 1; lin ++)
{
    for (auto it : v[lin])
    {
        int pos = it.second;
        dp0[pos] = 0, dp1[pos] = 1 << lin;
        for (int i=0; i<lin; i++)
            askAndUpdate (it.first, i, lin, dp1[pos], dp0[pos]);

        long long curr = 1LL << (F - 1 - lin), x = 1LL * dp0[pos] * curr, y = 1LL * dp1[pos] * curr;
        ans -= y, ans += x;
    }
    if (lin < F - 1)
    {
        trieRoot[lin] = ++nodes;
        for (auto it : v[lin])
            add (it.first, lin, dp0[it.second], dp1[it.second]);
    }
}
//for (int i=1; i<=N; i++)
  //  printf ("(%lld, %lld)\n", dp0[i], dp1[i]);
printf ("%lld\n", ans);
return 0;
}
