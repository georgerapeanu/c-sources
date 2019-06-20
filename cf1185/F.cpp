#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 1e5;
const int inf = 1 << 30;
const int LGMAX = 9;///0...LGMAX - 1 bits are used

int n,m;
int custom[NMAX + 5];
int pizza[MMAX + 5];
int cost[MMAX + 5];

pair<int,int> merg(pair<int,int> a,pair<int,int> b) {
    vector<pair<int,int> > v = {{cost[a.first],a.first},{cost[a.second],a.second},{cost[b.first],b.first},{cost[b.second],b.second}};

    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end()) - v.begin());

    return {v[0].second,v[1].second};
}

long long eval(pair<int,int> a) {
    return 1LL * cost[a.first] + 1LL * cost[a.second];
}

int cnt_sub[1 << LGMAX];
pair<int,int> best_pizzas[1 << LGMAX];

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= n; i++) {
        int l;
        scanf("%d",&l);
        for(int j = 1; j <= l; j++) {
            int x;
            scanf("%d",&x);
            x--;
            custom[i] |= (1 << x);
        }
        cnt_sub[custom[i]]++;
    }

    cost[0] = inf;
    for(int i = 1; i <= m; i++) {
        int l;
        scanf("%d %d",&cost[i],&l);
        for(int j = 1; j <= l; j++) {
            int x;
            scanf("%d",&x);
            x--;
            pizza[i] |= (1 << x);
        }
    }

    for(int b = 0; b < LGMAX; b++) {
        for(int i = 0; i < (1 << LGMAX); i++) {
            if((i >> b) & 1) {
                cnt_sub[i] += cnt_sub[i ^ (1 << b)];
            }
        }
    }

    for(int i = 1; i <= m; i++) {
        best_pizzas[pizza[i]] = merg(best_pizzas[pizza[i]], {0,i});
    }

    int best_cnt = -inf;
    pair<int,int> bst = {0,0};

    for(int m1 = 0; m1 < (1 << LGMAX); m1++) {
        for(int m2 = m1; m2 < (1 << LGMAX); m2++) {
            if(best_pizzas[m1] == make_pair(0,0) || best_pizzas[m2] == make_pair(0,0)) {
                continue;
            }
            int tmp_cnt = cnt_sub[m1 | m2];
            pair<int,int> tmp;
            if(m1 == m2) {
                if(best_pizzas[m1].second == 0) {
                    continue;
                }
                tmp = best_pizzas[m1];
            }
            else {
                tmp = {best_pizzas[m1].first,best_pizzas[m2].first};
            }
            if(best_cnt < tmp_cnt || (best_cnt == tmp_cnt && eval(bst) >= eval(tmp))) {
                best_cnt = tmp_cnt;
                bst = tmp;
            }
        }
    }

    cout << bst.first << " " << bst.second;

    return 0;
}
