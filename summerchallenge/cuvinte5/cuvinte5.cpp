#include <fstream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

ifstream f("cuvinte5.in");
ofstream g("cuvinte5.out");

const int LMAX = 7;
const int NMAX = 50;
const int QMAX = 2500;

int n,q;
string a,b,c[NMAX + 5];

int d[LMAX + 5][LMAX + 5];
int dist(const string &a,const string &b) {
    d[0][0] = 0;
    for(int i = 1; i < (int)a.size(); i++) {
        d[i][0] = i;
    }
    for(int i = 1; i < (int)b.size(); i++) {
        d[0][i] = i;
    }

    for(int i = 1; i < (int)a.size(); i++) {
        for(int j = 1; j < (int)b.size(); j++) {
            d[i][j] = min(min(d[i - 1][j],d[i][j - 1]) + 1,d[i - 1][j - 1] + (a[i] != b[j]));
        }
    }
    return d[(int)a.size() - 1][(int)b.size() - 1] * d[(int)a.size() - 1][(int)b.size() - 1];
}

int de[NMAX + 5][NMAX + 5];
int curr[NMAX + 5][NMAX + 5];
int ans[QMAX + 5];

int tmp[NMAX + 5][NMAX + 5];
int da[NMAX + 5];
int db[NMAX + 5];

struct data_t {
    int id;
    string a,b;

    data_t(int id,const string &a,const string &b) {
        this->id = id;
        this->a = a;
        this->b = b;
    }
};

int main() {

    f >> n;

    for(int i = 1; i <= n; i++) {
        f >> c[i];
        c[i] = " " + c[i];
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            de[i][j] = dist(c[i],c[j]);
        }
    }

    f >> q;

    vector<data_t> v[NMAX + 5];

    for(int i = 1; i <= q; i++) {
        int k;
        f >> k >> a >> b;
        a = " " + a;
        b = " " + b;
        v[k].push_back({i,a,b});
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            curr[i][j] = (i == j ? 0 : (1 << 26));
        }
    }

    for(auto it:v[1]) {
        ans[it.id] = dist(it.a,it.b);
    }

    for(int stage = 2; stage <= n + 1; stage++) {
        for(auto it:v[stage]) {
            ans[it.id] = dist(it.a,it.b);
            for(int i = 1; i <= n; i++) {
                da[i] = dist(it.a,c[i]);
                db[i] = dist(it.b,c[i]);
            }
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    ans[it.id] = min(ans[it.id],da[i] + curr[i][j] + db[j]);
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                tmp[i][j] = (1 << 26);
                for(int k = 1; k <= n; k++) {
                    tmp[i][j] = min(tmp[i][j],curr[i][k] + de[k][j]);
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                curr[i][j] = min(tmp[i][j],curr[i][j]);
            }
        }
    }

    for(int i = 1; i <= q; i++) {
        g << ans[i] << "\n";
    }

    f.close();
    g.close();

    return 0;
}
