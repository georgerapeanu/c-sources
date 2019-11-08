#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e3;
const int BMAX = 5e4;
const int VMAX = 1e3;

int n,m;

int a[NMAX + 5][NMAX + 5];
int dp[NMAX + 5][NMAX + 5][3];

int aib[VMAX + 5];
long long val_aib[VMAX + 5];

void reset_aib() {
    memset(aib,0,sizeof(aib));
}

void update_aib(int pos,int val) {
    for(; pos <= VMAX; pos += (-pos) & pos) {
        aib[pos] += val;
        val_aib[pos] += pos * val;
    }
}

int query_aib(int pos) {
    int sum = 0;

    for(; pos; pos -= (-pos) & pos) {
        sum += aib[pos];
    }
    return sum;
}

int find_median() {
    int total = query_aib(VMAX);

    int pos = 0,cnt = 0;

    for(int step = 1 << 15; step; step >>= 1) {
        if(pos + step <= VMAX && cnt + aib[pos ^ step] * 2 <= total) {
            pos += step;
            cnt += aib[pos];
        }
    }

    return pos + 1;
}

long long query_sum(int pos) {
    long long ans = 0;

    for(; pos; pos -= (-pos) & pos) {
        ans += val_aib[pos];
    }
    return ans;
}

vector<pair<int,int> > ok(int len) {
    vector<pair<int,int> > ans;
    for(int i = len - 1; i < n; i++) {
        reset_aib();
        for(int j = 0; j < m; j++) {
            for(int k = i - len + 1; k <= i; k++) {
                up_aib(a[k][j],1);
                if(j >= len - 1) {
                    up_aib(a[k][j - len + 1],-1);
                }
            }
            if(j >= len - 1) {
                int med = find_median();
                long long cost = (1LL * query_aib(med) * med - query_sum(med)) + ((query_sum(VMAX) - query_sum(med) - 1LL * (query_aib(VMAX) - query_aib(med)) * med));
                if(cost <= 1LL * budget) {
                    ans.push_back(i - len + 1,j - len + 1);
                }
            }
        }
    }
    return ans;
}

int main() {

    scanf("%d %d",&n,&m);
    scanf("%d",&budget);
    int mi = 1e9,ma = -1e9;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d",&a[i][j]);
        }
    }

    int len = 0;
    vector<pair<int,int> > pos;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            a[i][j]--;
            for(int k = 0; k < 3; k++) {
                dp[i][j][k] = do_dp(i,j,k);
                a[i][j]++;
                if(len < dp[i][j][k]) {
                    len = dp[i][j][k];
                    pos.clear();
                    pos.push_back({i - len + 1,j - len + 1});
                }
                else if(len == dp[i][j][k]) {
                    pos.push_back({i - len + 1,j - len + 1});
                }
            }
            a[i][j] -= 2;
        }
    }

    sort(pos.begin(),pos.end());
    pos.resize(unique(pos.begin(),pos.end()) - pos.begin());

    auto cmp1 = [&](pair<int,int> a,pair<int,int> b) {
        if(a.first != b.first) {
            return a.first < b.first;
        }
        return a.second < b.second;
    };
    auto cmp2 = [&](pair<int,int> a,pair<int,int> b) {
        if(a.second != b.second) {
            return a.second < b.second;
        }
        return a.first < b.first;
    };

    sort(pos.begin(),pos.end(),cmp1);

    printf("%d\n",len);

    for(auto it:pos) {
        printf("%d %d\n",it.second,it.first);
    }


    return 0;
}
