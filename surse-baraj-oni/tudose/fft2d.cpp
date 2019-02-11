#include <bits/stdc++.h>

using namespace std;

ifstream fin ("fft2d.in");
ofstream fout ("fft2d.out");

const int lim = (1<<15) + 5;
typedef long long ll;

bool black[16][lim];
int F, T;
ll ans = 0, dp[16][lim];
vector< vector<ll> > bad;

void brute()
{
    int h, x, i, j;
    while(T--)
    {
        fin >> h >> x;
        black[h][x] = 1;
    }

    for(i=0; i<(1<<(F-1)); ++i)
        dp[F-1][i] = !(black[F-1][i]);

    for(i=F-2; i>=0; --i)
        for(j=0; j<(1<<(F-1)); ++j)
        {
            dp[i][j] = dp[i+1][j] + dp[i+1][j ^ (1<<(F-i-2))];
            if(black[i][j]) dp[i][j] = 0;
        }

    for(i=0; i<(1<<(F-1)); ++i)
        ans += dp[0][i];
    fout << ans << '\n';
}

struct Triee
{
    Triee *son[2];
    ll val;

    Triee()
    {
        val = 0;
        son[0] = son[1] = NULL;
    }

    void update(int lev, ll A, ll add)
    {
        val += add;
        if(!lev) return;

        int go = A & 1LL;
        if(!son[go]) son[go] = new Triee();

        son[go] -> update(lev-1, A/2, add);
    }

    ll query(int lev, ll A)
    {
        if(!lev) return val;
        int go = A & 1LL;
        if(!son[go]) return 0;
        return son[go] -> query(lev-1, A/2);
    }

} *Root = new Triee();

struct Trie
{
    Trie *son[2];
    vector<ll> a;

    Trie()
    {
        son[0] = son[1] = NULL;
        a.clear();
    }

    void baga(int lev, ll node, ll A)
    {
        if(!lev)
        {
            a.push_back(A);
            return;
        }

        int go = ((node & (1LL << (lev-1))) > 0 ? 1 : 0);
        if(!son[go]) son[go] = new Trie();
        son[go] -> baga(lev-1, node, A);
    }

    void dfs(int lev)
    {
        int i;

        if(a.size())
        {
            bad.push_back( vector<ll> () );
            bad.back().resize(a.size());

            for(i=0; i<a.size(); ++i)
            {
                bad.back()[i] = (1LL << (F-1-lev)) - Root -> query(lev, a[i]);
                ans -= bad.back()[i] * (1LL << lev);
            }

            for(i=0; i<a.size(); ++i)
                Root -> update(lev, a[i], bad.back()[i]);
        }

        if(son[0]) son[0] -> dfs(lev-1);
        if(son[1]) son[1] -> dfs(lev-1);

        if(a.size())
        {
            for(i=0; i<a.size(); ++i)
                Root -> update(lev, a[i], -bad.back()[i]);
            bad.pop_back();
        }
    }

} *root;


int main()
{
    int h;
    ll x, A, B;
    fin >> F >> T;

    if(F <= 16)
    {
        brute();
        return 0;
    }

    root = new Trie();
    while(T--)
    {
        fin >> h >> x;
        A = x & ( (1LL << (F-h-1)) - 1 );
        B = (x >> (F-h-1));
        root -> baga(h, B, A);
    }

    ans = (1LL << (2*F - 2));
    root -> dfs(F-1);
    fout << ans << '\n';

    return 0;
}
