#include <bits/stdc++.h>

using namespace std;

map<int,int> prov;
vector<int> box[20];

int k;
vector<pair<int,int> > pos[1 << 15];
long long sum[20];
bool dp[1 << 15];

pair<int,int> ans[20];

int main() {

    scanf("%d",&k);

    long long target = 0;

    for(int i = 1; i <= k; i++) {
        int n;
        scanf("%d",&n);
        for(int j = 1; j <= n; j++) {
            int x;
            scanf("%d",&x);
            prov[x] = i;
            box[i].push_back(x);
            target += x;
            sum[i] += x;
        }
    }

    if(target % k != 0) {
        printf("No");
        return 0;
    }

    target /= k;

    for(int i = 1; i <= k; i++) {
        for(auto it:box[i]) {
            int conf = (1 << (i - 1));
            int curr = i;
            int elem = it;
            vector<pair<int,int> > op;
            bool ok = true;
            while(true) {
                long long nxt_elem = target - (sum[curr] - elem);
                if(nxt_elem > 1e9 || nxt_elem < -1e9) {
                    ok = false;
                    break;
                }
                if(nxt_elem == it) {
                    op.push_back({nxt_elem,curr});
                    break;
                }
                if(prov.count(nxt_elem) == 0 || ((conf >> (prov[nxt_elem] - 1)) & 1) == true) {
                    ok = false;
                    break;
                }
                op.push_back({nxt_elem,curr});
                curr = prov[nxt_elem];
                conf ^= (1 << (curr - 1));
                elem = nxt_elem;
            }
            if(ok) {
                pos[conf] = op;
                dp[conf] = true;
            }
        }
    }

    for(int conf = 0; conf < (1 << k); conf++) {
        if(dp[conf]) {
            continue;
        }
        for(int conf2 = conf; conf2; conf2 = ((conf2 - 1) & conf)) {
            if(dp[conf2] && dp[conf ^ conf2]) {
                dp[conf] = true;
                for(auto it:pos[conf2]) {
                    pos[conf].push_back(it);
                }
                for(auto it:pos[conf ^ conf2]) {
                    pos[conf].push_back(it);
                }
                break;
            }
        }
    }

    if(dp[(1 << k) -1] == false) {
        printf("No\n");
        return 0;
    }

    printf("Yes\n");

    for(auto it:pos[(1 << k) - 1]) {
        ans[prov[it.first]] = it;
    }

    for(int i = 1; i <= k; i++) {
        printf("%d %d\n",ans[i].first,ans[i].second);
    }

    return 0;
}
