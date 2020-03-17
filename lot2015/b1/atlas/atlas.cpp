#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("atlas.in","r");
FILE *g = fopen("atlas.out","w");

const int NMAX = 1e5;
const int VMAX = 1e5;
const long long inf = 1e17;

int t,n,q;
int h[NMAX + 5];
long long max_hold[NMAX + 5];
long long pref_sum[NMAX + 5];
int st[NMAX + 5],len;
vector<pair<long long,int> > query[NMAX + 5];

pair<int,pair<long long,long long> > ans[NMAX + 5];

long long gcd(long long a,long long b) {
    if(b == 0) {
        return a;
    }

    return gcd(b,a % b);
}

int main() {

    fscanf(f,"%d",&t);

    while(t--) {
        fscanf(f,"%d",&n);
        for(int i = 1; i <= n; i++) {
            fscanf(f,"%d",&h[i]);
            pref_sum[i] = pref_sum[i - 1] + h[i];
            query[i].clear();
        }

        h[0] = h[n + 1] = VMAX + 5;
        max_hold[0] = 0;
        st[len = 1] = 0;

        for(int i = 1; i <= n; i++) {
            while(len > 0 && h[st[len]] < h[i]) {
                len--;
            }
            max_hold[i] = max_hold[st[len]] + 1LL * h[i] * (i - st[len]) - (pref_sum[i] - pref_sum[st[len]]);
            st[++len] = i;
        }

        max_hold[n + 1] = inf;

        fscanf(f,"%d",&q);

        for(int i = 1; i <= q; i++) {
            long long val;
            fscanf(f,"%lld",&val);

            int l = 1,r = n + 1;

            while(r - l > 1) {
                int mid = (l + r) / 2;
                if(max_hold[mid] >= val) {
                    r = mid;
                }
                else {
                    l = mid;
                }
            }

            query[l].push_back({val,i});
        }

        max_hold[0] = 0;
        st[len = 1] = 0;
        for(int i = 1; i <= n; i++) {
            while(len > 0 && h[st[len]] < h[i]) {
                len--;
            }
            st[++len] = i;

            for(auto it:query[i]) {
                long long val = it.first;
                int id = it.second;
                int l = 0,r = len;
                while(r - l > 1) {
                    int mid = (l + r) / 2;
                    if(val - max_hold[st[mid]] <= 1LL * h[st[mid]] * (st[len] - st[mid]) - (pref_sum[st[len]] - pref_sum[st[mid]])) {
                        l = mid;
                    }
                    else {
                        r = mid;
                    }
                }
                val -= max_hold[st[l]];
                long long sus = val + (pref_sum[st[len]] - pref_sum[st[l]]);
                long long jos = st[len] - st[l];
                long long ___g = gcd(sus,jos);
                sus /= ___g;
                jos /= ___g;
                ans[id] = {i,{sus,jos}};
            }
        }

        for(int i = 1; i <= q; i++) {
            fprintf(g,"%d %lld/%lld\n",ans[i].first,ans[i].second.first,ans[i].second.second);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
