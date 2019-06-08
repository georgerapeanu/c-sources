#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <random>

using namespace std;

const int NMAX = 3e5;

int n;
int v[NMAX + 5];
int pos[NMAX + 5],len;

unsigned long long map_to[NMAX + 5];
unsigned long long pref[NMAX + 5];
unsigned long long target[NMAX + 5];
int main() {

    random_device rd;
    mt19937_64 gen(rd());

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&v[i]);
        map_to[i] = gen();
        if(v[i] == 1) {
            pos[++len] = i;
        }
    }

    for(int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] ^ map_to[v[i]];
        target[i] = target[i - 1] ^ map_to[i];
    }

    pos[++len] = n + 1;

    long long ans = 0;

    for(int i = 1; i < len; i++) {
        int at = pos[i];
        int l = pos[i - 1];
        int r = pos[i + 1];

        int m_val = 0;

        for(int k = at; k < r; k++) {
            m_val = max(m_val,v[k]);
            if(m_val <= k && (pref[k] ^ pref[k - m_val]) == target[m_val]) {
                ans++;
            }
        }

        m_val = 1;

        for(int k = at - 1; k > l; k--) {
            m_val = max(m_val,v[k]);
            if(m_val + k - 1 <= n && (pref[k + m_val - 1] ^ pref[k - 1]) == target[m_val]) {
                ans++;
            }
        }
    }

    printf("%lld\n",ans);

    return 0;
}
