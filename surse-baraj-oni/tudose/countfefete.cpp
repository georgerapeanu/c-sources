#include <bits/stdc++.h>

using namespace std;

ifstream fin  ("countfefete.in");
ofstream fout ("countfefete.out");

const int Nmax = 2e5 + 5;
const int Mod = 1e9 + 7;
const int L = 30;
typedef long long ll;

int val[Nmax], x, y, i, n, ways0[L+2], ways1[L+2], Size, pw2[2*Nmax];
vector<int> v[Nmax];
int ans = 0;
bool impare[L+2], I[L+2], used[Nmax];
pair<int, int> S[Nmax];

void add_to(int &x, int y)
{
    x += y;
    if(x>=Mod) x -= Mod;
}

void sub_to(int &x, int y)
{
    x -= y;
    if(x < 0) x += Mod;
}

int inm(int x, int y)
{
    return (ll) x * y % Mod;
}

void dfs(int node, int dad)
{
    int i;
    ++Size;
    for(i=0; i<L; ++i)
        if(val[node] & (1<<i)) I[i] = 1;

    for(auto it : v[node])
        if(it != dad && !used[it]) dfs(it, node);
}

void taie(int node)
{
    int i, all = 0;

    memset(impare, 0, sizeof(impare));

    memset(ways0, 0, sizeof(ways0));
    memset(ways1, 0, sizeof(ways1));

    for(auto it : v[node])
        if(!used[it])
        {
            Size = 0;
            memset(I, 0, sizeof(I));
            dfs(it, node);
            all += Size;

            for(i=0; i<L; ++i)
                if(I[i])
                {
                    impare[i] = 1;
                    sub_to( ways0[i], pw2[Size - 1] - 1 );
                    sub_to( ways1[i], pw2[Size - 1] );
                }
                else sub_to( ways0[i], pw2[Size] - 1 );
        }

    for(i=0; i<L; ++i)
        if(!impare[i]) add_to( ways0[i], pw2[all] - 1 ), ways1[i] = 0;
            else add_to( ways0[i], pw2[all - 1] - 1 ), add_to( ways1[i], pw2[all - 1] );

    for(i=0; i<L; ++i)
        if(val[node] & (1<<i))
        {
            add_to(ans, inm(1<<i, ways0[i]) );
            if(impare[i]) add_to(ans, inm(1<<i, pw2[all - 1]));
              //  else add_to(ans, inm(1<<i, 1<<all));
        }
        else
        {
            add_to(ans, inm(1<<i, ways1[i]) );
            if(impare[i]) add_to(ans, inm(1<<i, pw2[all - 1]) );
        }

    used[node] = 1;
}

int main()
{
    fin >> n;
    for(i=1; i<=n; ++i) fin >> val[i];

    for(i=1; i<n; ++i)
    {
        fin >> x >> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }

    pw2[0] = 1;
    for(i=1; i<=2*n; ++i) pw2[i] = inm(pw2[i-1], 2);

    for(i=1; i<=n; ++i) S[i] = {val[i], i};
    sort(S+1, S+n+1);

    for(i=1; i<=n; ++i)
        taie(S[i].second);

    fout << ans << '\n';
    return 0;
}
