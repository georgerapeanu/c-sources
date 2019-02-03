#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

FILE *f = fopen("fpwl.in","r");
FILE *g = fopen("fpwl.out","w");

const int NMAX = 1e6;

class AIB {
public:

    pair<int,int> aib[NMAX + 5];

    AIB() {
        memset(aib,0,sizeof(aib));
    }

    void update(int pos,pair<int,int> val) {
        for(; pos < NMAX + 5; pos += (-pos) & pos) {
            aib[pos] = max(aib[pos],val);
        }
    }

    pair<int,int> query(int pos) {
        pair<int,int> val = {0,0};
        for(; pos; pos -= (-pos) & pos) {
            val = max(val,aib[pos]);
        }
        return val;
    }
};

int n,k;
int v[NMAX + 5];
int sgn[NMAX + 5];
pair<int,int> dp[NMAX + 5];

pair<int,int> exact[NMAX + 5];
AIB pref;
AIB suff;

int get_sgn(int pos) {
    return sgn[(pos - 1) % k + 1];
}

int main() {

    fscanf(f,"%d %d",&n,&k);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
    }

    fscanf(f,"\n");

    for(int i = 1; i <= n; i++) {
        char c;
        fscanf(f,"%c ",&c);
        sgn[i] = (c == '>' ? 1 : (c == '=' ? 0 : -1));
    }

    int ind = 0;

    for(int i = 1; i <= n; i++) {
        dp[i] = max(dp[i], {1,0});
        dp[i] = max(dp[i],exact[v[i]]);
        dp[i] = max(dp[i],suff.query(v[i]));
        dp[i] = max(dp[i],pref.query(NMAX + 1 - v[i]));
        if(get_sgn(dp[i].first) == -1) {
            suff.update(v[i] + 1, {dp[i].first + 1,i});
        }
        else if(get_sgn(dp[i].first) == 0) {
            exact[v[i]] = max(exact[v[i]], {dp[i].first + 1,i});
        }
        else {
            pref.update(NMAX + 2 - v[i], {dp[i].first + 1,i});
        }
        if(dp[i] > dp[ind]) {
            ind = i;
        }
    }

    fprintf(g,"%d\n",dp[ind].first);
    vector<int> ans;
    while(ind) {
        ans.push_back(v[ind]);
        ind = dp[ind].second;
    }
    reverse(ans.begin(),ans.end());
    for(auto it:ans) {
        fprintf(g,"%d ",it);
    }

    return 0;
}

