#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 2000;
const int LMAX = 2000;

int n,l;
int v[NMAX + 5][LMAX + 5];
pair<long long,long long> split[NMAX + 5][NMAX + 5];
long long sum[NMAX + 5];
bool seen[NMAX + 5];
vector<int> perm;

long long gcd(long long a,long long b) {
    if(!b) {
        return a;
    }
    return gcd(b,a % b);
}

bool cmp_frac(const pair<long long,long long> &a,const pair<long long,long long> &b) {
    return (long double)a.first / a.second < (long double)b.first / b.second;
}

int main() {

    scanf("%d %d",&n,&l);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= l; j++) {
            scanf("%d",&v[i][j]);
            sum[i] += v[i][j];
        }
    }

    for(int i = 1; i <= n; i++) {
        long long curr = 0;
        int last = 0;

        for(int j = 1; j <= n; j++) {
            while(last < l && cmp_frac({curr,1}, {sum[i] * j,n})) {
                last++;
                curr += v[i][last];
            }
            if(j == n) {
                split[i][j] = {l,1};
            }
            else {
                split[i][j] = {1LL * last * n * v[i][last] + sum[i] * j - curr * n,n * v[i][last]};
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        int id = -1;
        for(int j = 1; j <= n; j++) {
            long long g = gcd(split[j][i].first,split[j][i].second);
            split[j][i].first /= g;
            split[j][i].second /= g;
            if(seen[j]) {
                continue;
            }
            if(id == -1 || cmp_frac(split[j][i],split[id][i])) {
                id = j;
            }
        }

        if(i < n) {
            printf("%lld %lld\n",split[id][i].first,split[id][i].second);
        }
        perm.push_back(id);
        seen[id] = true;
    }

    for(auto it:perm) {
        printf("%d ",it);
    }

    return 0;
}
