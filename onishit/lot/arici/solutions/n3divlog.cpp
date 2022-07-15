#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
template<class T> void check_min(T &a, const T &b){ a = (a < b) ? a : b; }
template<class T> void check_max(T &a, const T &b){ a = (a > b) ? a : b; }
#define all(x) (x).begin(), (x).end()

const int N = 35e2 + 3;

int n;
array<int, 3> p[N];
pair<int, bitset<N>> dp[N];

void merge(pair<int, bitset<N>> &l, const pair<int, bitset<N>> &r){
    if(r.first > l.first){
        l = r;
    }
    else if(l.first == r.first){
        l.second |= r.second;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    p[0] = {0, 0, 0};
    for(int i = 1; i <= n; ++i){
        cin >> p[i][0] >> p[i][1] >> p[i][2];
        --p[i][2];
    }
    sort(p, p + 1 + n);

    dp[0].second[0] = true;
    for(int i = 1; i <= n; ++i){
        for(int j = 0; j < i; ++j){
            if(p[j][1] > p[i][1])
                continue;
            if(dp[j].first + 1 > dp[i].first){
                dp[i].first = dp[j].first + 1;
                dp[i].second = dp[j].second << p[i][2];
            }
            else if(dp[j].first + 1 == dp[i].first){
                dp[i].second |= dp[j].second << p[i][2];
            }
        }
    }

    for(int i = 0; i < n; ++i)
        merge(dp[n], dp[i]);

    int sum = dp[n].first;
    cout << sum << " ";

    int best;
    for(int i = sum / 2; i >= 0; --i){
        if(dp[n].second[i] || dp[n].second[sum - i]){
            best = i;
            break;
        }
    }
    int diff = abs(best - (sum - best));
    cout << diff << "\n";
}