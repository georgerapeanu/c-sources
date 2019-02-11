#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int N, M, K;
LL ans;
int a[25][66005];
int sz[25][66005];

int main()
{
    freopen("fft2d.in", "r", stdin);
    freopen("fft2d.out", "w", stdout);

    scanf("%d%d", &N, &K);
    M = (1 << (N - 1));
    for(int i = 1; i <= K; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        a[x][y] = 1;
    }

    for(int i = 0; i < M; i++)
        sz[0][i] = a[0][i] ^ 1;

    for(int i = 1; i < N; i++)
    {
        int bt = (N - 1 - i);
        int p = (1 << bt);
        for(int j = 0; j < M; j++)
            if(a[i][j] == 0)
                sz[i][j] = sz[i - 1][j] + sz[i - 1][j ^ p];
    }

    for(int i = 0; i < M; i++)
        if(a[N - 1][i] == 0)
            ans += sz[N - 1][i];

    printf("%lld\n", ans);

    return 0;
}
