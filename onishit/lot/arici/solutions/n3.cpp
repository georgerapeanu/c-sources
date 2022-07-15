#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <bitset>
#include <set>

using namespace std;

template<class T> void check_min(T &a, const T &b){ a = (a < b) ? a : b; }
template<class T> void check_max(T &a, const T &b){ a = (a > b) ? a : b; }

const int MAXN = 15e3;

struct Fruit
{
    int x, y;
    int type;
};

int n, X, Y;
Fruit a[MAXN+5];

int dp[MAXN+5];
int findLongest()
{
    int ans = 0;
    for(int i = 0;i<n;i++)
    {
        dp[i] = 1;
        for(int j = 0;j<i;j++)
        {
            if(a[j].y<=a[i].y)
                dp[i] = max(dp[i], dp[j]+1);
        }

        ans = max(ans, dp[i]);
    }

    return ans;
}

set <int> possibleCounts;
bool seenState[MAXN+5][MAXN+5];

void rec(int ind, int cnt)
{
    if(dp[ind]==1)
    {
        possibleCounts.insert(cnt);
        return;
    }

    if(seenState[ind][cnt]==true) return;
    seenState[ind][cnt] = true;

    for(int i = 0;i<ind;i++)
    {
        if(a[i].y<=a[ind].y && dp[i]+1==dp[ind])
            rec(i, cnt+(a[i].type==1));
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;X = Y = n;
    for(int i = 0;i<n;i++)
    {
        cin >> a[i].y >> a[i].x >> a[i].type;
    }
    sort(a, a+n, [](const Fruit& A, const Fruit& B)
    {
        if(A.x!=B.x) return A.x<B.x;
        return A.y<B.y;
    });

    int ans = findLongest();
    int bestBalance = MAXN;

    for(int i = 0;i<n;i++)
        if(dp[i]==ans) rec(i, (a[i].type==1));

    for(int x: possibleCounts)
        bestBalance = min(bestBalance, abs(x - (ans - x)));

    cout << ans << " " << bestBalance << '\n';
}
/*
5 10
4
1 5 1
2 2 2
4 2 1
5 9 2

4
1 3 1
2 4 1
3 1 2
4 2 2
*/
