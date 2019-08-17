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

pair<long long,long long>lines[NMAX + 5];

struct incr_cht_stack_t {
    vector<pair<long long,long long> > lines;
    int sz;

    incr_cht_stack_t() {
        lines.clear();
        sz = 0;
    }

    void add(const pair<long long,long long> &line) {
        while(sz > 1 && double(lines[sz - 2].second - lines[sz - 1].second) / (lines[sz - 1].first - lines[sz - 2].first) >=
                double(line.second - lines[sz - 1].second) / (lines[sz - 1].first - line.first)) {
            sz--;
            lines.pop_back();
        }
        sz++;
        lines.push_back(line);
    }

    long long query(long long x) {
        if(sz == 0) {
            return -(1LL << 62);
        }

        int st = 0,dr = (int)lines.size() - 1;

        while(dr - st > 1) {
            int mid = (st + dr) / 2;
            if(double(lines[mid + 1].second - lines[mid].second) / (lines[mid].first - lines[mid + 1].first) <= x) {
                st = mid;
            }
            else {
                dr = mid;
            }
        }

        return max(lines[st].first * x + lines[st].second,lines[dr].first * x + lines[dr].second);
    }

    void flush() {
        sz = 0;
        lines.clear();
    }

} snd_hull;

struct decr_cht_stack_t {
    vector<pair<long long,long long> > lines;
    int sz;

    decr_cht_stack_t() {
        lines.clear();
        sz = 0;
    }

    void add(const pair<long long,long long> &line) {
        while(sz > 1 && double(lines[sz - 2].second - lines[sz - 1].second) / (lines[sz - 1].first - lines[sz - 2].first) <=
                double(line.second - lines[sz - 1].second) / (lines[sz - 1].first - line.first)) {
            sz--;
            lines.pop_back();
        }
        sz++;
        lines.push_back(line);
    }

    long long query(long long x) {
        if(sz == 0) {
            return -(1LL << 62);
        }

        int st = 0,dr = (int)lines.size() - 1;

        while(dr - st > 1) {
            int mid = (st + dr) / 2;
            if(double(lines[mid + 1].second - lines[mid].second) / (lines[mid].first - lines[mid + 1].first) >= x) {
                st = mid;
            }
            else {
                dr = mid;
            }
        }

        return max(lines[st].first * x + lines[st].second,lines[dr].first * x + lines[dr].second);
    }

    void flush() {
        sz = 0;
        lines.clear();
    }

} fst_hull;


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

    vector<pair<pair<int,int>,int> > fst_ord;
    vector<pair<pair<int,int>,int> > snd_ord;

    int fst_le = 0,snd_le = 0,fst_ri = -1,snd_ri = -1;
    int le = 0,ri = -1;

    for(int i = 0; i <= n; i++) {
        fst_ri++;
        ri++;
        while(leftmost[i] > le) {
            if(snd_ri - snd_le + 1 > 0) {
                snd_le++;
                le++;
            }
            else {
                snd_le = fst_le;
                snd_ri = fst_ri;
                fst_le = i + 1;
                fst_ri = i;
            }
        }
        fst_ord.push_back({{fst_le,fst_ri},i});
        snd_ord.push_back({{snd_le,snd_ri},i});
    }

    reverse(snd_ord.begin(),snd_ord.end());

    /*for(auto it:snd_ord){
        printf("%d %d %d\n",it.first.first,it.first.second,it.second);
    }*/

    for(int h = 1; h <= k; h++) {
        for(int i = 0; i <= n; i++) {
            lines[i] = {-2 * pref[i],pref[i] * pref[i] + dp[i]};
            dp[i] = 0;
        }
        int le = -1,ri = -1;
        for(auto it:fst_ord) {
            if(le != it.first.first) {
                fst_hull.flush();
                for(int j = it.first.first; j <= it.first.second; j++) {
                    fst_hull.add(lines[j]);
                }
                le = it.first.first;
                ri = it.first.second;
            }
            else {
                while(ri < it.first.second) {
                    ri++;
                    fst_hull.add(lines[ri]);
                }
            }
            /*printf("fst %d %d %d\n",it.first.first,it.first.second,it.second);
            for(auto it:fst_hull.lines){
                printf("%d %d\n",it.first,it.second);
            }*/
            dp[it.second] = max(dp[it.second],pref[it.second] * pref[it.second] + fst_hull.query(pref[it.second]));
        }

        le = -1,ri = -1;
        for(auto it:snd_ord) {
            if(ri != it.first.second) {
                snd_hull.flush();
                for(int j = it.first.second; j >= it.first.first; j--) {
                    snd_hull.add(lines[j]);
                }
                le = it.first.first;
                ri = it.first.second;
            }
            else {
                while(le > it.first.first) {
                    le--;
                    snd_hull.add(lines[le]);
                }
            }/*
            printf("snd %d %d %d\n",it.first.first,it.first.second,it.second);
            for(auto it:snd_hull.lines){
                printf("%d %d\n",it.first,it.second);
            }*/
            dp[it.second] = max(dp[it.second],pref[it.second] * pref[it.second] + snd_hull.query(pref[it.second]));
        }
        for(int i = 1; i <= n; i++) {
            dp[i] = max(dp[i - 1],dp[i]);
        }/*
        for(int i = 0;i <= n;i++){
            printf("%d ",dp[i]);
        }
        printf("\n");*/
    }

    fprintf(g,"%lld\n",dp[n]);

    fclose(f);
    fclose(g);

    return 0;
}
