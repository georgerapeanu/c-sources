#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 2e5;
const int QMAX = 5e5;
const int LGMAX = 18;

int n,q;
string s[NMAX + 5];

pair<int,int> sa[NMAX + 5];///(from,index)
int pos[LGMAX + 5][NMAX + 5];

int len_sa;
int gap;

pair<int,int> segm[NMAX + 5];

int ans[QMAX + 5];
int sp[NMAX + 5];

struct query_t {
    int sgn;
    int val;
    int l,r;
    int id;

    bool operator < (const query_t &other)const {
        if(val != other.val) {
            return val < other.val;
        }

        return id < other.id;
    }
};

vector<query_t> v;


bool cmp(pair<int,int> a,pair<int,int> b) {
    if(pos[gap][sp[a.first - 1] + a.second] != pos[gap][sp[b.first - 1] + b.second]) {
        return pos[gap][sp[a.first - 1] + a.second] < pos[gap][sp[b.first - 1] + b.second];
    }

    if(a.second + (1 << gap) >= (int)s[a.first].size() || b.second + (1 << gap) >= (int)s[b.first].size()) {
        return (int)s[a.first].size() - a.second < (int)s[b.first].size() - b.second;
    }

    a.second += (1 << gap);
    b.second += (1 << gap);

    return pos[gap][sp[a.first - 1] + a.second] < pos[gap][sp[b.first - 1] + b.second];
}

void build_sa() {
    int len = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < (int)s[i].size(); j++) {
            sa[++len] = {i,j};
            pos[0][sp[i - 1] + j] = (s[i][j] - 'a') + 1;
        }
    }

    sort(sa + 1,sa + 1 + len,
    [](pair<int,int> a,pair<int,int> b) {
        if(s[a.first][a.second] != s[b.first][b.second]) {
            return s[a.first][a.second] < s[b.first][b.second];
        }

        if((int)s[a.first].size() - a.second != (int)s[b.first].size() - b.second) {
            return (int)s[a.first].size() - a.second < (int)s[b.first].size() - b.second;
        }
        return a.first < b.first;
    }
        );

    for(gap = 0; (1 << gap) <= sp[n]; gap++) {
        sort(sa + 1,sa + 1 + len,cmp);
        pos[gap + 1][sp[sa[1].first - 1] + sa[1].second] = 1;
        int lst_pos = 1;
        for(int i = 2; i <= len; i++) {
            pos[gap + 1][sp[sa[i].first - 1] + sa[i].second] = (lst_pos += cmp(sa[i - 1],sa[i]));
        }
    }
    len_sa = len;
}

int lcp(pair<int,int> x,pair<int,int> y) {
    int ans = 0;
    for(int lvl = gap; lvl >= 0; lvl--) {
        if(x.second < (int)s[x.first].size() &&
                y.second < (int)s[y.first].size() &&
                pos[lvl][sp[x.first - 1] + x.second] == pos[lvl][sp[y.first - 1] + y.second]) {

            x.second += (1 << lvl);
            y.second += (1 << lvl);
            ans += (1 << lvl);
        }
    }
    return ans;
}

int aib[NMAX + 5];

void u(int pos,int val) {
    for(; pos <= NMAX; pos += (-pos) & pos) {
        aib[pos] += val;
    }
}

int qu(int pos) {
    int ans = 0;
    for(; pos; pos -= (-pos & pos)) {
        ans += aib[pos];
    }

    return ans;
}

int main() {

    cin >> n >> q;

    for(int i = 1; i <= n; i++) {
        cin >> s[i];
        sp[i] = sp[i - 1] + (int)s[i].size();
    }

    build_sa();

    for(int i = 1; i <= len_sa; i++) {
        if(sa[i].second == 0) {
            int st,dr;

            st = 0,dr = i;

            while(dr - st > 1) {
                int mid = (st + dr) / 2;

                if(lcp(sa[mid],sa[i]) >= (int)s[sa[i].first].size()) {
                    dr = mid;
                }
                else {
                    st = mid;
                }
            }

            segm[sa[i].first].first = dr;

            st = i,dr = len_sa + 1;

            while(dr - st > 1) {
                int mid = (st + dr) / 2;

                if(lcp(sa[mid],sa[i]) >= (int)s[sa[i].first].size()) {
                    st = mid;
                }
                else {
                    dr = mid;
                }
            }

            segm[sa[i].first].second = st;
        }
    }

    for(int i = 1; i <= q; i++) {
        int l,r,k;
        scanf("%d %d %d",&l,&r,&k);

        v.push_back({-1,l - 1,segm[k].first,segm[k].second,i});
        v.push_back({1,r,segm[k].first,segm[k].second,i});
    }

    for(int i = 1; i <= len_sa; i++) {
        v.push_back({0,sa[i].first,i,i,0});
    }

    sort(v.begin(),v.end());

    for(auto it:v) {
        if(it.sgn == 0) {
            u(it.l,1);
        }
        else {
            ans[it.id] += it.sgn * (qu(it.r) - qu(it.l - 1));
        }
    }

    for(int i = 1; i <= q; i++) {
        printf("%d\n",ans[i]);
    }

    return 0;
}
