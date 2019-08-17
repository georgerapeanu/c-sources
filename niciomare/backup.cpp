#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("niciomare.in","r");
FILE *g = fopen("niciomare.out","w");

const int NMAX = 1e5;
const int KMAX = 100;
const int SMAX = 1e8;
const int SZ = 10;

int n,k,s;
int v[NMAX + 5];
int leftmost[NMAX + 5];
long long pref[NMAX + 5];
long long dp[NMAX + 5];

struct cht_t {
    vector<pair<long long,long long> > lines;
    int sz;
    int lst_ans;

    cht_t() {
        sz = 0;
        lines.clear();
    }

    void clear() {
        lines.clear();
        sz = 0;
        lst_ans = 0;
    }

    void add(const pair<long long,long long> &line) {
        while(sz > 1 && double(lines[sz - 1].second - lines[sz - 2].second) / (lines[sz - 2].first - lines[sz - 1].first) <= double(line.second - lines[sz - 1].second) / (lines[sz - 1].first - line.first)) {
            sz--;
            lines.pop_back();
        }
        lines.push_back(line);
        lst_ans = sz;
        sz++;
    }

    long long query(long long x) {

        while(lst_ans > 0 && lines[lst_ans - 1].first * x + lines[lst_ans - 1].second >= lines[lst_ans].first * x + lines[lst_ans].second) {
            lst_ans--;
        }

        return lines[lst_ans].first * x + lines[lst_ans].second;
    }
};

cht_t aint[2 * NMAX + 5];

inline void clear_aint() {
    for(int i = 1; i <= 2 * n; i++) {
        aint[i].clear();
    }
}

void update(int pos,const pair<long long,long long> &lin) {
    pos++;
    for(pos += n; pos; pos >>= 1) {
        aint[pos].add(lin);
    }
}

long long query(int l,int r,long long pos) {
    l++;
    r++;
    long long ans = -1e18;
    for(l += n,r += n; l < r; l >>=1,r >>=1) {
        if(l & 1)ans = max(ans,aint[l++].query(pos));
        if(r & 1)ans = max(ans,aint[--r].query(pos));
    }
    return ans;
}

inline pair<long long,long long> make_line(const long long &sum,const long long &dp) {
    return {-2 * sum,sum * sum + dp};
}

int main() {

    fscanf(f,"%d %d %d",&n,&k,&s);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
        pref[i] = v[i] + pref[i - 1];
    }

    leftmost[n + 1] = n + 1;
    for(int i = n; i >= 0; i--) {
        leftmost[i] = min(i,leftmost[i + 1]);
        while(leftmost[i] > 0 && pref[i] - pref[leftmost[i] - 1] <= s) {
            leftmost[i]--;
        }
    }

    for(int h = 1; h <= k; h++) {
        clear_aint();

        for(int i = 0; i <= n; i++) {
            update(i,make_line(pref[i],dp[i]));
        }
        for(int i = 1; i <= n; i++) {
            dp[i] = max(max(dp[i],dp[i - 1]),query(leftmost[i],i,pref[i]) + pref[i] * pref[i]);
        }
    }

    fprintf(g,"%lld\n",dp[n]);

    fclose(f);
    fclose(g);

    return 0;
}
