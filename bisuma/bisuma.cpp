#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

FILE *f = fopen("bisuma.in","r");
FILE *g = fopen("bisuma.out","w");

const int NMAX = 1e5;
const long long inf = 1e15;

int n,k;
long long dp[2][NMAX + 5];
long long a[NMAX + 5];
long long b[NMAX + 5];

const int LEN = 1 << 14;
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

    while(buff[ind] >= '0' && buff[ind] <= '9') {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int last = 0;
class SegTree {
    long long aint[4 * NMAX + 5];
public:
    void reset() {
        for(int i = 1; i <= 4 * last; i++) {
            aint[i] = inf;
        }
    }
    void update(int pos,long long val) {
        pos += last;
        aint[pos] = min(aint[pos],val);
        for(; pos > 1; pos >>= 1) {
            aint[pos >> 1] = min(aint[pos],aint[pos ^ 1]);
        }
    }
    long long query(int l,int r) {
        r++;
        long long ans = inf;
        for(l += last,r += last; l < r; (l >>= 1),(r >>= 1)) {
            if(l & 1)ans = min(ans,aint[l++]);
            if(r & 1)ans = min(ans,aint[--r]);
        }
        return ans;
    }
};

SegTree fst,snd;

int main() {

    n = i32();
    k = i32();

    long long ans = 0;

    for(int i = 1; i <= n; i++) {
        a[i] = i32();
        ans += a[i];
    }

    for(int i = 1; i <= n; i++) {
        b[i] = i32();
        b[i] -= a[i];
    }

    map<long long,int> to_norm;

    to_norm[0] = 1;

    for(int i = 1; i <= n; i++) {
        b[i] += b[i - 1];
        to_norm[b[i]] = 1;
    }
    for(auto &it:to_norm) {
        it.second = ++last;
    }

    for(int i = 1; i <= n; i++) {
        dp[0][i] = inf;
    }

    for(int h = 1; h <= k; h++) {
        dp[h & 1][0] = inf;
        fst.reset();
        snd.reset();
        fst.update(to_norm[b[0]],dp[1 - (h & 1)][0]);
        snd.update(to_norm[b[0]],dp[1 - (h & 1)][0] - b[0]);
        for(int i = 1; i <= n; i++) {
            dp[h & 1][i] = inf;
            dp[h & 1][i] = min(dp[h & 1][i],snd.query(1,to_norm[b[i]]) + b[i]);
            dp[h & 1][i] = min(dp[h & 1][i],fst.query(to_norm[b[i]],last));
            fst.update(to_norm[b[i]],dp[1 - (h & 1)][i]);
            snd.update(to_norm[b[i]],dp[1 - (h & 1)][i] - b[i]);
        }
    }

    fprintf(g,"%lld ",dp[k & 1][n] + ans);

    fclose(f);
    fclose(g);

    return 0;
}
