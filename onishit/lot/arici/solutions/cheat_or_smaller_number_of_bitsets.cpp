#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#include <set>

using namespace std;

template<class T> void check_min(T &a, const T &b){ a = (a < b) ? a : b; }
template<class T> void check_max(T &a, const T &b){ a = (a > b) ? a : b; }

const int MAXN = 1e5;

struct Fruit
{
    int x, y;
    int type;
};

int n, X, Y;
Fruit a[MAXN+5];

int dp[MAXN];

set <int> all;

int seenSz = 0;
set <int> seen[MAXN+5];
void rec(int ind, int cnt)
{
    if(dp[ind]==1)
    {
        //all.insert(cnt);
        return;
    }

    if(seen[ind].count(cnt)==true) return;
    {
        seen[ind].insert(cnt);
        seenSz++;

//        if(seenSz%1000==0) cout << "seenSz: " << seenSz << '\n';
    }

    int goal = dp[ind] - 1;
    for(int i = 0;i<ind;i++)
    {
        if(dp[i]==goal && a[i].y<=a[ind].y) rec(i, cnt+(a[i].type==1));
    }
}

struct Fenwick{
    int a[MAXN+5];

    void update(int i, int val){
        ++i;
        for(; i < MAXN; i += i & -i)
            check_max(a[i], val);
    }

    int query(int i){
        ++i;
        int res = 0;
        for(; i >= 1; i -= i & -i)
            check_max(res, a[i]);
        return res;
    }
} f;

vector <int> val2Inds[MAXN+5];
bitset <MAXN+5> possibleSums[MAXN+5];

int findLIS()
{
    val2Inds[0].push_back(n);

    a[n].y = 0;
    possibleSums[n][0] = true;

    for(int i = 0; i < n; ++i)
    {
        dp[i] = f.query(a[i].y) + 1;

        f.update(a[i].y, dp[i]);
        val2Inds[dp[i]].push_back(i);

        possibleSums[i].reset();
        for(int j = (int)val2Inds[dp[i]-1].size()-1, iter = 0;j>=0 && iter<19;j--, iter++)
        {
            if(a[val2Inds[dp[i]-1][j]].y>a[i].y) break;
            possibleSums[i] |= possibleSums[val2Inds[dp[i]-1][j]];
        }

        if(a[i].type==0) possibleSums[i] <<= 1;
    }

    return dp[n-1];
}

pair<int, int> collectFruits(int N, std::vector<int> x, std::vector<int> y, std::vector<int> z)
{

    n = N;
    X = Y = n;
    for(int i = 0;i<n;i++)
    {
        a[i].y = x[i];
        a[i].x = y[i];
        a[i].type = z[i];
        a[i].type--;
    }
    a[n] = {Y, X, 1};n++;
    sort(a, a+n, [](const Fruit& A, const Fruit& B)
    {
        if(A.x!=B.x) return A.x<B.x;
        return A.y<B.y;
    });

    int lis = findLIS();
    //cout << lis << '\n';

    int bestBalance = MAXN;
    for(int a = 0;a<=lis;a++)
    {
        if(possibleSums[n-1][a]==true)
        {
            bestBalance = min(bestBalance, abs(a - ((lis-1)-a)));
        }
    }

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
