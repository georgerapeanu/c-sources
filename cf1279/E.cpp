#include <bits/stdc++.h>

using namespace std;

int t;
int n;
long long k;
long long fact[100];
long long dp[100];

int head[100];
int tail[100];

const long long inf = 2e18;

void gen(int n,long long k,int shift) {
    set<int> vals;

    for(int i = shift + 1; i < shift + n; i++) {
        vals.insert(i);
        head[i] = i;
        tail[i] = i;
    }

    int lst = 1;

    printf("%d ",shift + n);

    head[shift + 1] = shift + n;
    tail[shift + n] = shift + 1;

    while(lst < n) {
        for(auto &it:vals) {
            if(lst < n - 1 && it == tail[(lst + 1) + shift]) {
                continue;
            }
            if(lst < n - 1 && k > fact[n - lst - 2]) {
                k -= fact[n - lst - 2];
            }
            else {
                printf("%d ",it);
                tail[head[it]] = tail[(lst + 1) + shift];
                head[tail[(lst + 1) + shift]] = head[it];
                vals.erase(it);
                lst++;
                break;
            }
        }
    }
}

int main() {

    fact[0] = 1;

    for(int i = 1; i <= 99; i++) {
        if(fact[i - 1] < inf / i) {
            fact[i] = fact[i - 1] * i;
        }
        else {
            fact[i] = inf;
        }
    }

    dp[0] = 1;
    dp[1] = 1;

    for(int i = 2; i <= 99; i++) {
        for(int j = 0; j < i; j++) {
            long long tmp = 0;
            if(dp[j] < inf / fact[max(0,i - j - 2)]) {
                tmp = dp[j] * fact[max(0,i - j - 2)];
            }
            else {
                tmp = inf;
            }
            if(dp[i] < inf - tmp) {
                dp[i] += tmp;
            }
            else {
                dp[i] = inf;
            }
        }
    }

    scanf("%d",&t);

    while(t--) {
        scanf("%d %lld",&n,&k);
        int lst = 0;
        vector<int> v;
        while(lst < n) {
            bool ok = false;
            for(int i = lst + 1; i <= n; i++) {
                if(dp[n - i] < inf / fact[max(0,i - lst - 2)] && k > dp[n - i] * fact[max(0,i - lst - 2)]) {
                    k -= dp[n - i] * fact[max(0,i - lst - 2)];
                }
                else {
                    long long id_perm = (k - 1) / dp[n - i];
                    k -= id_perm * dp[n - i];
                    id_perm++;
                    gen(i - lst,id_perm,lst);
                    lst = i;
                    ok = true;
                    break;
                }
            }
            if(ok) {
                continue;
            }
            v = {-1};
            lst = n;
        }
        for(auto it:v) {
            printf("%d ",it);
        }
        printf("\n");
    }

    return 0;
}
