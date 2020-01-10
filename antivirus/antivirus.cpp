#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("antivirus.in","r");
FILE *g = fopen("antivirus.out","w");

int t;
int n,k;
int v[2005];

vector< vector<int> > stuff;

int sp[2005];
int dp[2005][2005];
int len[2005];

void process(int st,int dr) {
    if(st > dr) {
        return ;
    }

    int l = dr - st + 1;
    int sum = sp[dr] - sp[st - 1];
    vector<int> ans(l + 1,sum);
    for(int k = 0; k <= l; k++) {
        for(int i = st + (l - k) - 1; i <= dr; i++) {
            ans[k] = min(ans[k],sum - (sp[i] - sp[i - (l - k)]));
        }
    }

    stuff.push_back(ans);
}

void process_suff(int st,int dr) {
    if(st > dr) {
        return ;
    }

    int l = dr - st + 1;
    vector<int> ans(l + 1,1e9);
    for(int k = 0; k <= l; k++) {
        ans[k] = min(ans[k],(sp[st + k - 1] - sp[st - 1]));
    }

    stuff.push_back(ans);
}

void process_pref(int st,int dr) {
    if(st > dr) {
        return ;
    }

    int l = dr - st + 1;
    vector<int> ans(l + 1,1e9);
    for(int k = 0; k <= l; k++) {
        ans[k] = min(ans[k],(sp[dr] - sp[dr - k]));
    }

    stuff.push_back(ans);
}

int main() {

    fscanf(f,"%d",&t);

    while(t--) {
        fscanf(f,"%d %d",&n,&k);
        v[0] = v[n + 1] = 0;
        for(int i = 1; i <= n; i++) {
            fscanf(f,"%d",&v[i]);
            sp[i] = sp[i - 1] + v[i];
        }

        int last = 0;
        stuff.clear();
        for(int i = 1; i <= n; i++) {
            if(v[i] == 0) {
                if(last) {
                    process(last + 1,i - 1);
                }
                else {
                    process_pref(1,i - 1);
                }
                k--;
                last = i;
            }
        }

        process_suff(last + 1,n);

        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= k; j++) {
                dp[i][j] = 2e9;
            }
            len[i] = 0;
        }

        dp[0][0] = 0;
        len[0] = 0;

        for(int i = 0; i < (int)stuff.size(); i++) {
            len[i + 1] = min(k,len[i] + (int)stuff[i].size() - 1);
            for(int j = 0; j <= len[i]; j++) {
                for(int l = 0; l < (int)stuff[i].size() && j + l <= k; l++) {
                    dp[i + 1][j + l] = min(dp[i + 1][j + l],dp[i][j] + stuff[i][l]);
                }
            }
        }

        fprintf(g,"%d\n",dp[(int)stuff.size()][k]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
