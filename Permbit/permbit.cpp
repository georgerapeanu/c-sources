#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("permbit.in","r");
FILE *g = fopen("permbit.out","w");

const int BASE = 2;
const int MOD = 1e9 + 7;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int NMAX = 1e6;

struct hsh_t {
    int h1,h2;

    hsh_t() {
        h1 = h2 = 0;
    }

    void add(int val) {
        h1 = (h1 * BASE + val) % MOD1;
        h2 = (h2 * BASE  + val)% MOD2;
    }

    bool operator < (const hsh_t &other)const {
        if(h1 == other.h1) {
            return h1 < other.h1;
        }
        return h2 < other.h2;
    }
};

int c;
int n,m;
pair<hsh_t,hsh_t> stuff[NMAX + 5];

char tmp[NMAX + 5];

map<hsh_t,vector<int> > eq_class;

int fact[NMAX + 5];

int main() {

    fscanf(f,"%d\n",&c);
    fscanf(f,"%d %d\n",&n,&m);

    fact[0] = 1;
    for(int i = 1; i <= m; i++) {
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    }
    for(int i = 1; i <= n; i++) {
        fgets(tmp + 1,NMAX + 5,f);
        for(int j = 1; j <= m; j++) {
            if(i < n) {
                stuff[j].first.add(tmp[j] - '0');
            }
            if(1 < i) {
                stuff[j].second.add(tmp[j] - '0');
            }
        }
    }

    for(int i = 1; i <= m; i++) {
        eq_class[stuff[i].second].push_back(i);
    }

    if(c <= 2) {
        bool found = false;
        for(int i = 1; i <= m; i++) {
            if(found == true) {
                fprintf(g,"%d ",eq_class[stuff[i].first].back());
                eq_class[stuff[i].first].pop_back();
            }
            else {
                vector<int> &tmp = eq_class[stuff[i].first];
                if(tmp.size() % 2 == 1) {
                    fprintf(g,"%d ",tmp[(int)tmp.size() / 2]);
                    eq_class[stuff[i].first].erase(tmp.begin() + ((int)tmp.size() / 2));
                }
                else {
                    fprintf(g,"%d ",tmp[(int)tmp.size() / 2 - 1]);
                    eq_class[stuff[i].first].erase(tmp.begin() + ((int)tmp.size() / 2) - 1);
                    found = true;
                }
            }
        }
    }
    else {
        int ans = 1;
        for(auto it:eq_class) {
            ans = 1LL * ans * fact[it.second.size()] % MOD;
        }
        fprintf(g,"%d\n",ans);
    }



    return 0;
}
