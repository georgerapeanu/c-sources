#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

const int NMAX = 50;
const int LMAX = 20;

int n,l;
char c[NMAX + 5][LMAX + 5];

long long bad[1 << LMAX];
double cnt[LMAX];

int get_mask(const int &a,const int &b) {
    int ans = 0;
    for(int i = 0; i < l; i++) {
        if(c[a][i + 1] == c[b][i + 1]) {
            ans ^= (1 << i);
        }
    }
    return ans;
}

int num_bits(long long conf) {
    int ans = 0;
    for(; conf; conf ^= ((-conf) & conf)) {
        ans++;
    }
    return ans;
}

int main() {

    fscanf(stdin,"%d\n",&n);

    for(int i = 1; i <= n; i++) {
        fgets(c[i] + 1,LMAX + 5,stdin);
    }

    l = strlen(c[1] + 1);
    l -= (c[1][l] == '\n');

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i != j) {
                bad[get_mask(i,j)] |= (1LL << i);
            }
        }
    }

    for(int conf = (1 << l) - 1; conf >= 0; conf--) {
        for(int i = 0; i < l; i++) {
            bad[conf] |= bad[conf | (1 << i)];
        }
    }

    for(int conf = 0; conf < (1 << l); conf++) {
        cnt[num_bits(conf)] += num_bits(bad[conf]);
    }

    double ans = 0;

    double p = 1;

    for(int i = 0; i <= l; i++) {
        ans += cnt[i] * p / n;
        p = p * (i + 1) / (l - i);
    }

    fprintf(stdout,"%.17f",ans);

    return 0;
}
