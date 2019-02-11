#include<bits/stdc++.h>

using namespace std;

int N, s, sir[510009], pi[510009];

int getSmart (int pos, int s)
{
    int ans = 0;
    while (pos > 0)
        ans += pos % s, pos /= s;
    return ans % s;
}

int main ()
{
freopen ("pscfft.in", "r", stdin);
freopen ("pscfft.out", "w", stdout);

int tests;
scanf ("%d", &tests);
while (tests --)
{
    scanf ("%d %d", &N, &s);
    for (int i=1; i<=N; i++)
        scanf ("%d", &sir[i]);
    sir[N + 1] = -1;
    int k = 0, ans = -1;
    for (int i=2; i<=N; i++)
    {
        while (k != 0 && sir[k + 1] != sir[i]) k = pi[k];
        if (k < N && sir[k + 1] == sir[i]) k ++;
        pi[i] = k;
    }
    k = 0;
    for (int i=0; i<500000 + N - 1; i++)
    {
        int curr = getSmart (i, s);
        while (k != 0 && sir[k + 1] != curr) k = pi[k];
        if (k < N && sir[k + 1] == curr)
        {
            k ++;
            if (k == N)
            {
                ans = i - N + 1;
                break;
            }
        }
    }
    printf ("%d\n", ans);
}
return 0;
}
