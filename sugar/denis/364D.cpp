#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>
#include <ctime>

using namespace std;

const int NMAX = 1e6;

int n;
long long v[NMAX + 5];
long long tmp[NMAX + 5];

long long gcd(long long a,long long b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

long long solve(long long val) {
    long long backup_val = val;
    vector<long long> fact;
    vector<long long> divs;
    unordered_map<long long,int> state;

    for(int i = 1; 1LL * i * i <= val; i++) {
        if(val % i == 0) {
            divs.push_back(i);
            if(val / i != i) {
                divs.push_back(val / i);
            }
        }
    }

    sort(divs.begin(),divs.end());

    for(int i = 0; i < (int)divs.size(); i++) {
        state[divs[i]] = i;
    }

    for(int i = 2; 1LL * i * i <= val; i++) {
        if(val % i == 0) {
            fact.push_back(i);
            while(val % i == 0) {
                val /= i;
            }
        }
    }

    if(val != 1) {
        fact.push_back(val);
    }

    val = backup_val;

    vector<int> dp(divs.size(),0);

    for(int i = 1; i <= n; i++) {
        tmp[i] = gcd(v[i],val);
        dp[state[tmp[i]]]++;
    }

    for(int i = 0; i < (int)fact.size(); i++) {
        for(int j = (int)divs.size() - 1; j >= 0; j--) {
            if(divs[j] <= ((long long)1e18) / fact[i] && state.count(divs[j] * fact[i])) {
                dp[j] += dp[state[divs[j] * fact[i]]];
            }
        }
    }

    long long best = -1;

    for(int i = 0; i < (int)divs.size(); i++) {
        if(dp[i] >= (n + 1) / 2) {
            best = divs[i];
        }
    }

    return best;
}

int main() {

    srand(time(NULL));

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%lld",&v[i]);
    }

    long long ans = -1;

    for(int attempt = 0; attempt < 10; attempt++) {
        int pos = (rand() << 15);
        pos ^= rand();
        if(pos < 0) {
            pos ^= ((1LL << 32) - 1);
        }
        pos = pos % n + 1;
        ans = max(ans,solve(v[pos]));
    }

    printf("%lld\n",ans);

    return 0;
}
