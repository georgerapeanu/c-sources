#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int N, S, K;
int v[500005], aux[500005];

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

void solve_test()
{
    N = gint();
    S = gint();
    for(int i = 1; i <= N; i++)
        v[i] = gint();

    int ans = 0;
    int pw = 1;
    int pos = 1;
    while(N > 0)
    {
        if(N == 1)
        {
            ans += (1LL * v[1] * pw) % mod;
            ans %= mod;
            break;
        }

        if(N <= S)
        {
            int start = -1;
            int pos = 0;
            int lst = 0;
            for(int i = 1; i < N; i++)
            {
                lst = i;
                if( (v[i] + 1) % S != v[i + 1] )
                {
                    start = (v[i] + 1) % S;
                    pos = i % S;
                    break;
                }
            }
            for(int i = lst + 1; i < N; i++)
                if( (i % S) != pos && (v[i] + 1) % S != v[i + 1] )
                {
                    printf("-1\n");
                    return;
                }
            if(start == -1)
            {
                if(N == S)  start = v[1];
                else
                {
                    if(v[1] < v[N]) start = 0;
                    else    start = (v[N] + 1) % S;
                }
            }
            ans += (1LL * ((v[1] - start + S) % S) * pw) % mod;
            ans %= mod;
            pw = (1LL * pw * S) % mod;

            K = 1;
            if((v[1] - start + S) % S + N > S)
                aux[++K] = v[lst + 1];
            aux[1] = start;
            N = K;
            N = K;
            for(int i = 1; i <= N; i++) v[i] = aux[i];

            continue;
        }

        if(N <= 2 * S)
        {
            int start = -1;
            bool found = false;
            int lst = 0;
            int pos = 0;
            for(int i = 1; i < N; i++)
            {
                lst = i;
                if( (v[i] + 1) % S != v[i + 1] )
                {
                    found = true;
                    start = (v[i] + 1) % S;
                    pos = i % S;
                    break;
                }
            }
            for(int i = lst + 1; i < N; i++)
                if( (i % S) != pos && (v[i] + 1) % S != v[i + 1] )
                {
                    printf("-1\n");
                    return;
                }
            if(start == -1)
            {
                if(N == 2 * S)  start = v[1];
                else
                {
                    if(v[1] < v[N]) start = 0;
                    else    start = (v[N] + 1) % S;
                }
            }

            ans += (1LL * ((v[1] - start + S) % S) * pw) % mod;
            ans %= mod;
            pw = (1LL * pw * S) % mod;

            K = 0;
            //for(int i = 1; i <= N; i++) aux[i] = v[i];
            aux[++K] = start;
            if(lst > S) lst -= S;
            pos = lst + 1;
            if(found)
            {
                for(int i = pos; i <= N; i += S)
                    aux[++K] = v[i];
            }
            else
                aux[++K] = start;
            N = K;
            for(int i = 1; i <= N; i++) v[i] = aux[i];

            continue;
        }

        int start = 0;
        bool found = false;
        int lst = 0;
        int pos = 0;
        for(int i = 1; i <= 2 * S; i++)
        {
            lst = i;
            if( (v[i] + 1) % S != v[i + 1] )
            {
                found = true;
                start = (v[i] + 1) % S;
                pos = i % S;
            }
        }

        for(int i = lst + 1; i < N; i++)
            if( (i % S) != pos && (v[i] + 1) % S != v[i + 1] )
            {
                printf("-1\n");
                return;
            }

        ans += (1LL * ((v[1] - start + S) % S) * pw) % mod;
        ans %= mod;
        pw = (1LL * pw * S) % mod;

        if(lst > S) lst -= S;
        pos = lst + 1;

        K = 0;
        //for(int i = 1; i <= N; i++) aux[i] = v[i];
        aux[++K] = start;
        for(int i = pos; i <= N; i += S)
            aux[++K] = v[i];
        N = K;
        for(int i = 1; i <= N; i++) v[i] = aux[i];
    }

    printf("%d\n", ans);
}

int main()
{
    freopen("pscfft.in", "r", stdin);
    freopen("pscfft.out", "w", stdout);

    int T = gint();
    for(int t = 1; t <= T; t++)
        solve_test();

    return 0;
}
