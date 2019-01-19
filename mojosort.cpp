#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("mojosort.in","r");
FILE *g = fopen("mojosort.out","w");

const int NMAX = 300;
const int TMAX = 300;
const int INVMAX = (NMAX - 1) * (NMAX) / 2;

class ModularInt {
public:
    int val;
    int MOD;

    ModularInt(int val = 0,int MOD = 1e9 + 7) {
        this->val = val % MOD;
        this->MOD = MOD;
    }

    ModularInt operator + (const ModularInt &other)const {
        ModularInt ans(this->val + other.val,this->MOD);
        if(ans.val >= ans.MOD) {
            ans.val -= ans.MOD;
        }
        return ans;
    }

    ModularInt operator - (const ModularInt &other)const {
        ModularInt ans(this->val - other.val,this->MOD);
        if(ans.val < 0) {
            ans.val += ans.MOD;
        }
        return ans;
    }

    ModularInt operator * (const ModularInt &other)const {
        return ModularInt((1LL * this->val * other.val) % this->MOD,this->MOD);
    }

    ModularInt lgpow(ModularInt b,int e)const {
        ModularInt p(1);
        while(e) {
            if(e & 1) {
                p = p * b;
            }
            b = b * b;
            e >>= 1;
        }
        return p;
    }

    inline ModularInt inv()const {
        return lgpow(ModularInt(this->val,this->MOD),this->MOD - 2);
    }

    ModularInt operator / (const ModularInt &other)const {
        return *this * other.inv();
    }
};


int t;
int v[NMAX + 5];

double p[2][INVMAX + 5];
double sp[INVMAX + 5];
double ssp[INVMAX + 5];
double ans[TMAX + 5];

vector< pair<pair<int,int>,int> > queries[NMAX + 5];

ModularInt ip[2][INVMAX + 5];
ModularInt isp[INVMAX + 5];
ModularInt issp[INVMAX + 5];
ModularInt ians[TMAX + 5];

int main() {

    fscanf(f,"%d",&t);

    for(int x = 1; x <= t; x++) {
        int n,k,inv = 0;
        fscanf(f,"%d %d\n",&n,&k);
        for(int i = 1; i <= n; i++) {
            fscanf(f,"%d",&v[i]);
            for(int j = 1; j < i; j++) {
                inv += (v[j] > v[i]);
            }
        }
        queries[n].push_back({{min(k,n * (n - 1) / 2),inv},x});
    }

    for(int i = 1; i <= NMAX; i++) {
        sort(queries[i].begin(),queries[i].end());
    }

    p[0][0] = 1;
    ip[0][0] = ModularInt(1);

    for(int i = 1,l = 1; i <= NMAX; i++,l ^= 1) {
        double invi = (double)1 / i;
        ModularInt iinvi = ModularInt(i).inv();
        for(int j = 0; j <= (i - 1) * i / 2; j++) {
            p[l][j] = (j > 0 ? p[l][j - 1]:0) + (p[l ^ 1][j] - (j - i >= 0 ? p[l ^ 1][j - i] : 0)) * invi;
            sp[j] = p[l][j] + (j > 0 ? sp[j - 1]:0);
            ssp[j] = sp[j] + (j > 0 ? ssp[j - 1]:0);

            ip[l][j] = (j > 0 ? ip[l][j - 1]:0) + (ip[l ^ 1][j] - (j - i >= 0 ? ip[l ^ 1][j - i] : 0)) * iinvi;
            isp[j] = ip[l][j] + (j > 0 ? isp[j - 1]:0);
            issp[j] = isp[j] + (j > 0 ? issp[j - 1]:0);
        }
        if(queries[i].size()) {
            int curr = 0;
            double exp = i * (i - 1) / 2;
            ModularInt iexp(i * (i - 1) / 2);
            for(auto it:queries[i]) {
                while(curr < it.first.first) {
                    iexp = ModularInt((int)exp) * isp[curr + (int)exp] - issp[curr + (int)exp - 1] + issp[curr - 1] + iexp * (ModularInt(1) - isp[curr + (int)exp]);
                    exp = (int)exp * sp[curr + (int)exp] - ssp[curr + (int)exp - 1] + ssp[curr - 1] + exp * (1 - sp[curr + (int)exp]);
                    curr++;
                }
                if(it.first.second <= curr) {
                    ans[it.second] = 0;
                    ians[it.second] = ModularInt(0);
                }
                else if(it.first.second <= curr + (int)exp) {
                    ans[it.second] = it.first.second - curr;
                    ians[it.second] = ModularInt(it.first.second - curr);
                }
                else {
                    ans[it.second] = exp;
                    ians[it.second] = iexp;
                }
            }
        }
    }

    fprintf(g,"mojo\n");

    for(int i = 1; i <= t; i++) {
        fprintf(g,"%d\n",ians[i].val);
    }

    fclose(f);
    fclose(g);

    return 0;
}
