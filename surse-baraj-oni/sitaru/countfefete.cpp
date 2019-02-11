#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int N;
int v[200005], f[200005], ord[200005];
bool active[200005];
int cnt[200005][33][2];
int b[2], auxcnt[33][2];
vector<int> edg[200005];

int F(int x)
{
    if(f[x] == x)   return x;
    return f[x] = F(f[x]);
}

int add(int x, int y) { x += y; if(x >= mod) x -= mod; return x; }
int sub(int x, int y) { x -= y; if(x < 0) x += mod; return x; }
int mul(int x, int y) { return (1LL * x * y) % mod; }

int gint()
{
    char ch = getchar();
    while(ch < '0' || '9' < ch) ch = getchar();
    int x = 0;
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

int main()
{
    freopen("countfefete.in", "r", stdin);
    freopen("countfefete.out", "w", stdout);

    //scanf("%d", &N);
    N = gint();
    for(int i = 1; i <= N; i++)
        v[i] = gint();
        //scanf("%d", &v[i]);

    for(int i = 1; i < N; i++)
    {
        int x, y;
        //scanf("%d%d", &x, &y);
        x = gint();
        y = gint();
        edg[x].push_back(y);
        edg[y].push_back(x);
    }

    for(int i = 1; i <= N; i++) ord[i] = i;

    sort(ord + 1, ord + N + 1,
         [](int a, int b) { return v[a] > v[b]; });

    int ans = 0;
    for(int i = 1; i <= N; i++)
    {
        int nod = ord[i];
        int val = v[nod];

        active[nod] = true;
        f[nod] = nod;

        for(int i = 0; i < 30; i++)
        {
            cnt[nod][i][0] = cnt[nod][i][1] = 0;
            cnt[nod][i][ (val >> i) & 1 ]++;
            cnt[nod][i][0]++;
        }

        for(auto nxt: edg[nod])
        {
            if(!active[nxt])    continue;

            int fnxt = F(nxt);
            for(int i = 0; i < 30; i++)
            {
                b[0] = cnt[nod][i][0], b[1] = cnt[nod][i][1];

                cnt[nod][i][0] = add(0, add( mul(b[0], cnt[fnxt][i][0]), mul(b[1], cnt[fnxt][i][1]) ));
                cnt[nod][i][1] = add(0, add( mul(b[0], cnt[fnxt][i][1]), mul(b[1], cnt[fnxt][i][0]) ));
            }
        }

        for(int i = 0; i < 30; i++) auxcnt[i][0] = cnt[nod][i][0], auxcnt[i][1] = cnt[nod][i][1];

        for(auto nxt: edg[nod])
        {
            if(!active[nxt])    continue;

            int fnxt = F(nxt);
            for(int i = 0; i < 30; i++)
            {
                auxcnt[i][0] = sub(auxcnt[i][0], sub(cnt[fnxt][i][0], 1));
                auxcnt[i][1] = sub(auxcnt[i][1], cnt[fnxt][i][1]);
            }

            f[fnxt] = F(nod);
        }
        for(int i = 0; i < 30; i++) auxcnt[i][0] = sub(auxcnt[i][0], 1);

        int sol = 0;
        for(int i = 0; i < 30; i++)
        {
            int bt = ((val >> i) & 1);
            sol = add(sol, mul( (1 << i), auxcnt[i][bt ^ 1] ));
        }
        ans = add(ans, sol);
    }

    printf("%d\n", ans);

    return 0;
}
