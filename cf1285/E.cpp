#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int t;
int n;

int l[NMAX + 5];
int r[NMAX + 5];

map<int,int> to_norm;

int smen[4 * NMAX + 5];
int cnt0[4 * NMAX + 5];

vector<pair<int,int> > events[4 * NMAX + 5];

int aib[4 * NMAX + 5];

int last;

void update(int pos,int val) {
    for(; pos <= last; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

int query(int pos) {
    int ans = 0;
    for(; pos; pos -= (-pos) & pos) {
        ans += aib[pos];
    }
    return ans;
}

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d",&n);

        to_norm.clear();

        for(int i = 1; i <= n; i++) {
            scanf("%d",&l[i]);
            scanf("%d",&r[i]);
            to_norm[l[i]] = 1;
            to_norm[r[i]] = 1;
        }

        last = 0;

        for(auto &it:to_norm) {
            it.second = ++last;
        }

        for(int i = 1; i <= n; i++) {
            l[i] = to_norm[l[i]] * 2;
            r[i] = to_norm[r[i]] * 2;
            smen[l[i]]++;
            smen[r[i] + 1]--;
        }

        last = 2 * last + 1;

        int init = 0;
        int lst = 0;

        for(int i = 1; i <= last; i++) {
            events[i].clear();
            smen[i] += smen[i - 1];
            if(smen[i] == 0) {
                init += (lst != 0);
            }
            lst = smen[i];
            cnt0[i] = (smen[i] == 1);
        }

        for(int i = 1; i <= last; i++) {
            cnt0[i] += cnt0[i - 1];
        }

        for(int i = 1; i <= last; i++) {
            if(smen[i] == 1) {
                int fst = i;
                while(smen[i] == 1 && i <= last) {
                    i++;
                }
                i--;
                events[i + 1].push_back({0,fst - 1});
            }
        }

        for(int i = 1; i <= n; i++) {
            events[r[i]].push_back({1,l[i]});
        }

        int ans = -1e9;

        for(int i = 1; i <= last; i++) {
            sort(events[i].begin(),events[i].end());

            for(auto it:events[i]) {
                if(it.first == 0) {
                    update(it.second,1);
                }
                else {
                    ans = max(ans,init + (query(i) - query(it.second - 1)) - (cnt0[i] - cnt0[it.second - 1] == i - it.second + 1));
                }
            }
        }

        for(int i = 1; i <= last; i++) {
            smen[i] = 0;
            for(auto it:events[i]) {
                if(it.first == 0) {
                    update(it.second,-1);
                }
            }
        }
        printf("%d\n",ans);
    }

    return 0;
}
