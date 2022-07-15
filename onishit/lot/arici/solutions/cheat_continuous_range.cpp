#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#include "erinaceida.h"

using namespace std;

const int MAXN = 1e5;

struct Fruit
{
    int x, y;
    int type;
};

struct State
{
    int len;
    int minVal, maxVal;

    State(){}
    State(int len, int minVal, int maxVal) : len(len), minVal(minVal), maxVal(maxVal) {}
};

State combine(const State& s1, const State& s2)
{
    if(s1.len>s2.len) return s1;
    if(s2.len>s1.len) return s2;
    return State(s1.len, min(s1.minVal, s2.minVal), max(s1.maxVal, s2.maxVal));
}

int n, X, Y;
Fruit a[MAXN+5];

State dp[MAXN];

set <int> all;
set <pair <int, int>> seen;
void rec(int ind, int cnt)
{
    if(dp[ind].len==1)
    {
        all.insert(cnt);
        return;
    }

    if(seen.count(make_pair(ind, cnt))==true) return;
    seen.insert(make_pair(ind, cnt));

    int goal = dp[ind].len - 1;
    for(int i = 0;i<ind;i++)
    {
        if(dp[i].len==goal && a[i].y<=a[ind].y) rec(i, cnt+(a[i].type==1));
    }
}

int findLIS()
{
    for(int i = 0;i<n;i++)
    {
        dp[i] = State(1, (a[i].type==1), (a[i].type==1));
        for(int j = i-1;j>=0;j--)
        {
            if(a[j].y<=a[i].y)
            {
                State s = dp[j];

                s.len++;
                if(a[i].type==1)
                {
                    s.minVal++;
                    s.maxVal++;
                }

                dp[i] = combine(dp[i], s);
            }
        }
    }

    return dp[n-1].len;
}

pair<int, int> collectFruits(int N, std::vector<int> x, std::vector<int> y, std::vector<int> z)
{

    n = N;
    X = Y = n;

    for(int i = 0;i<n;i++) {
      a[i].y = x[i]; 
      a[i].x = y[i];
      a[i].type = z[i];
    }
    a[n] = {Y, X, 2};n++;
    sort(a, a+n, [](const Fruit& A, const Fruit& B)
    {
        if(A.x!=B.x) return A.x<B.x;
        return A.y<B.y;
    });

    int lis = findLIS();
    //cout << lis << '\n';

    rec(n-1, 0);
    //for(int x: all) cout << x << " ";
    //cout << '\n';

    //cout << dp[n-1].minVal << " -- " << dp[n-1].maxVal << '\n';
    //cout << all.size() << " == " << *prev(all.end()) - *all.begin() + 1 << '\n';

    int bestBalance = MAXN;
    for(int x = dp[n-1].minVal;x<=dp[n-1].maxVal;x++)
        bestBalance = min(bestBalance, (int)abs(x - ((lis-1)-x)));

    return {lis - 1, bestBalance};
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
