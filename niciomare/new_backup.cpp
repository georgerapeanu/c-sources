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
long long tmp_dp[NMAX + 5];

///we will multiply all by 2 to ease some computations
inline double sect(int i,int j) {
    return (pref[i] + pref[j]) + double(dp[i] - dp[j]) / (pref[i] - pref[j]);
}

const int LEN = 1 << 16;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;
    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while('0' <= buff[ind] && buff[ind] <= '9') {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

struct cht_t {
    vector<int> lines;
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

    void add(int line) {

        while(sz > 1 && sect(lines[sz - 1],lines[sz - 2]) <= sect(lines[sz - 1],line)) {
            sz--;
            lines.pop_back();
        }
        lines.push_back(line);
        lst_ans = sz;
        sz++;
    }

    long long query(int x) {

        while(lst_ans > 0 && sect(lines[lst_ans - 1],lines[lst_ans]) < 2 * pref[x]) {
            lst_ans--;
        }

        return dp[lines[lst_ans]] + (pref[x] - pref[lines[lst_ans]]) * (pref[x] - pref[lines[lst_ans]]);
    }
};

cht_t aint[2 * NMAX + 5];

inline void clear_aint() {
    for(int i = 1; i <= 2 * n; i++) {
        aint[i].clear();
    }
}

void update(int pos,const int &lin) {
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

int main() {

    n = i32();
    k = i32();
    s = i32();

    for(int i = 1; i <= n; i++) {
        v[i] = i32();
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
            update(i,i);
        }
        for(int i = 1; i <= n; i++) {
            tmp_dp[i] = max(dp[i],query(leftmost[i],i,i));
        }
        for(int i = 1; i <= n; i++) {
            dp[i] = max(dp[i - 1],tmp_dp[i]);
        }
    }

    fprintf(g,"%lld\n",dp[n]);

    fclose(f);
    fclose(g);

    return 0;
}
