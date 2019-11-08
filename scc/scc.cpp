#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e3;
const int BMAX = 1e9;
const int VMAX = 10000;

int n,m;

int a[NMAX + 5][NMAX + 5];

int aib[VMAX + 5];
long long val_aib[VMAX + 5];
int budget;

void reset_aib() {
    memset(aib,0,sizeof(aib));
    memset(val_aib,0,sizeof(val_aib));
}

void update_aib(int pos,int val) {
    int init = pos;
    for(; pos <= VMAX; pos += (-pos) & pos) {
        aib[pos] += val;
        val_aib[pos] += init * val;
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

    if(query_aib(pos + 1) * 2 - 1 <= total) {
        pos++;
    }

    return pos;
}

long long query_sum(int pos) {
    long long ans = 0;

    for(; pos; pos -= (-pos) & pos) {
        ans += val_aib[pos];
    }
    return ans;
}

vector<pair<int,int> > ok(int len,bool insta_return = false,bool deb = false) {
    vector<pair<int,int> > ans;
    reset_aib();
    for(int i = len - 1; i < n; i++) {
        for(int j = 0; j < m + len; j++) {
            for(int k = i - len + 1; k <= i; k++) {
                if(j < m) {
                    update_aib(a[k][j],1);
                }
                if(j >= len) {
                    update_aib(a[k][j - len],-1);
                }
            }
            if(j >= len - 1 && j < m) {
                int med = find_median();
                long long cost = (1LL * query_aib(med) * med - query_sum(med));
                cost += ((query_sum(VMAX) - query_sum(med)) - 1LL * (query_aib(VMAX) - query_aib(med)) * med);
                if(deb && i - len + 1 == 0 && j - len + 1 == 0 && len == 7) {
                    fprintf(stderr,"%d %d %d %d %lldcnt is %d and total %d\n",len,i,j,med,cost,query_aib(VMAX) - query_aib(med),query_aib(VMAX));
                }
                if(deb)fprintf(stderr,"%d %d %d %d %lld sum %lld\n",len,i,j,med,cost,query_sum(VMAX));
                if(cost <= 1LL * budget) {
                    ans.push_back({i - len + 1,j - len + 1});
                    if(insta_return) {
                        return ans;
                    }
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
            ma = max(ma,a[i][j]);
        }
    }


    int len = 0;
    vector<pair<int,int> > pos;

    int l = 0,r = min(n,m) + 1;

    while(r - l > 1) {
        int mid = (l + r) / 2;

        auto tmp = ok(mid,true,false);

        if(tmp.size() > 0) {
            pos = tmp;
            l = mid;
        }
        else {
            r = mid;
        }

    }

    len = l;
    ok(len,false,false);

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
