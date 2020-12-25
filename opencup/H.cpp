#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int inv2 = MOD / 2 + 1;

int n,m;
vector<int> a;

int solve(vector<int> values,int start){
    if(start > m){
        return n;
    }
    if(values.size() == 1){
        return values[0] < start;
    }

    int cost[2] = {0,0};
    vector<int> v[2];

    for(int i = 0;i < (int)values.size();i++){
        v[i & 1].push_back(values[i]);
        cost[i & 1] += (values[i] != start);
    }

    return min(solve(v[0],start + 1) + cost[1],solve(v[1],start + 1) + cost[0]);
}

int len[100005];
int fr[100005];

int get_elem(int val){
    int ans = 0;

    while(((1 << ans) & val) == 0){
        ans++;
    }
    return ans + 1;
}

int main(){

    len[1] = 1;

    for(int i = 2;i <= 100000;i++){
        len[i] = (2 * len[i - 1] + 1) % MOD;
    }

    while(scanf("%d %d",&n,&m) != EOF){
        a = vector<int>(n,0);
        for(int i = 0;i < n;i++){
            scanf("%d",&a[i]);
        }
        for(int i = 0;i < n;i++){
            fr[a[i]] = 0;
        }

        int sum = 1LL * n * (MOD + len[m] - n + 1) % MOD;

        for(int i = 0;i < n;i++){
            if(a[i] <= m){
                sum -= len[m - a[i]];
                if(sum < 0){
                    sum += MOD;
                }
                sum = (sum == 0 ? MOD - 1:sum - 1);
            }
        }

        for(int i = 1;i <= n;i++){
            sum += fr[a[i - 1]];
            if(sum >= MOD){
                sum -= MOD;
            }
            sum += fr[a[n - i]];
            if(sum >= MOD){
                sum -= MOD;
            }
            fr[get_elem(i)]++;
        }

        printf("%d %d\n",solve(a,1),sum);
    }

    return 0;
}
