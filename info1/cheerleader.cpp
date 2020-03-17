#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int h[1 << 17];
int ord[1 << 17];
int aib[(1 << 17) + 1];

vector<pair<int,int> > prio;
int cnt_bit = 0;
int mi,ma;

bool cmp(int a,int b) {
    for(int i = 0; i < (int)prio.size(); i++) {
        pair<int,int> it = prio[i];
        if(((a >> it.first) & 1) != ((b >> it.first) & 1)) {
            return (((a >> it.first) & 1) < ((b >> it.first) & 1)) ^  it.second;
        }
    }
    return a < b;
}

void reset() {
    memset(aib,0,sizeof(int) * ((1 << n) + 1));
}

void update(int pos,int val) {
    pos++;
    for(; pos >= mi; pos -= (-pos) & pos) {
        aib[pos] += val;
    }
}

long long query(int pos) {
    pos++;
    long long ans = 0;
    for(; pos <= ma; pos += (-pos) & pos) {
        ans += aib[pos];
    }
    return ans;
}

void SOR() {
    if(cnt_bit < n) {
        for(int st = 0; st < (1 << n); st += (1 << (n - cnt_bit))) {
            for(int fst = st; fst < st + (1 << (n - cnt_bit - 1)); fst++) {
                swap(ord[fst],ord[fst + (1 << (n - cnt_bit - 1))]);
            }
        }
    }
}

long long solve() {
    long long ans = 0;

    for(int st = 0; st < (1 << n); st += (1 << (n - cnt_bit))) {
        mi = 1e9,ma = -1e9;
        for(int fst = st; fst < st + (1 << (n - cnt_bit)); fst++) {
            mi = min(h[ord[fst]],mi);
            ma = max(h[ord[fst]],ma);
        }
        mi++;
        ma++;
        for(int fst = st; fst < st + (1 << (n - cnt_bit)); fst++) {
            update(h[ord[fst]],1);
            ans += query(h[ord[fst]]);
        }
        for(int fst = st; fst < st + (1 << (n - cnt_bit)); fst++) {
            update(h[ord[fst]],-1);
        }
    }

    return ans;
}

long long eval() {
    long long ans = 0;
    mi = 1;
    ma = (1 << n);
    for(int i = 0; i < (1 << n); i++) {
        ans += query(h[ord[i]]);
        update(h[ord[i]],1);
    }
    reset();
    return ans;
}

int main() {

    scanf("%d",&n);

    if(n == 0) {
        printf("0\n");
        return 0;
    }

    for(int conf = 0; conf < (1 << n); conf++) {
        scanf("%d",&h[conf]);
        ord[conf] = conf;
    }

    long long ans = 1e9;

    vector<pair<int,int> > best;

    prio.resize(n);

    for(int i = 0; i < n; i++) {

        for(int j = i; j >= 0; j--) {
            prio[i - j] = {j,0};
        }

        for(int j = n - 1; j > i; j--) {
            prio[i + n - j] = {j,0};
        }

        sort(ord,ord + (1 << n),cmp);

        cnt_bit = 0;

        for(int j = i; j >= 0; j--) {
            prio[i - j].second = 0;
            long long a = solve();
            prio[i - j].second = 1;
            SOR();
            long long b = solve();
            if(a < b) {
                prio[i - j].second = 0;
                SOR();
            }
            cnt_bit++;
        }
        for(int j = n - 1; j > i; j--) {
            prio[i + (n - j)].second = 0;
            long long a = solve();
            prio[i + (n - j)].second = 1;
            SOR();
            long long b = solve();
            if(a < b) {
                prio[i + (n - j)].second = 0;
                SOR();
            }
            cnt_bit++;
        }
        long long tmp = eval();
        if(ans > tmp) {
            ans = tmp;
            best = prio;
        }
    }

    printf("%lld\n",ans);

    for(int i = 0; i < best[n - 1].first; i++) {
        printf("2");
    }

    for(int i = n - 1; i >= 0; i--) {
        printf("2");
        if(best[i].second == 1) {
            printf("1");
        }
    }

    return 0;
}
