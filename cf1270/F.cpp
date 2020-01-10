#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int BUCK = 450;

string s;
int pref[NMAX + 5];
long long tmp[NMAX + 5];

long long get_valid_pos(int l,int r,int i,int mod) {
    if(l % mod <= i % mod) {
        l += (i % mod) - (l % mod);
    }
    else {
        l += (mod - (l % mod)) + (i % mod);
    }

    if(r % mod >= i % mod) {
        r -= (r % mod) - (i % mod);
    }
    else {
        r -= (r % mod) + (mod - (i % mod));
    }
    if(l > r) {
        return 0;
    }
    return (r - l) / mod + 1;
}

int main() {

    cin >> s;
    s = " " + s;

    for(int i = 1; i < (int)s.size(); i++) {
        pref[i] = pref[i - 1] + (s[i] == '1');
    }

    ///(pref[r] - pref[l - 1]) * k = r - (l - 1); 1 <= l,r <= n;
    ///pref[r] * k - r = pref[l - 1] * k - (l - 1),1 <= l,r <= n

    long long ans = 0;

    for(int k = 1; k <= BUCK; k++) {
        for(int i = 0; i < (int)s.size(); i++) {
            tmp[i] = 1LL * pref[i] * k - i;
        }

        sort(tmp,tmp + (int)s.size());

        int len = 0,lst = -1;

        for(int i = 0; i < (int)s.size(); i++) {
            if(lst != tmp[i]) {
                ans += 1LL * len * (len - 1) / 2;
                len = 0;
                lst = tmp[i];
            }
            len++;
        }
        ans += 1LL * len * (len - 1) / 2;
    }

    ///(r - l + 1) / (pref[r] - pref[l - 1]) > BUCK
    ///r - pref[r] * BUCK > (l - 1) - pref[l - 1] * BUCK
    ///r = i
    ///pref[r] - pref[l - 1] = k
    ///i - BUCK * k >= l
    for(int k = 1; k < (int)s.size() / BUCK; k++) {
        int lst = 0;
        int lst2 = 0;

        for(int i = 0; i < (int)s.size(); i++) {
            if(pref[i] < k) {
                continue;
            }
            while(pref[i] - pref[lst] > k) {
                lst++;
            }
            while(pref[i] - pref[lst2] >= k) {
                lst2++;
            }
            if(pref[i] - pref[lst] == k) {
                ///x included in [lst,lst2)
                ///k | i - x
                ///x = i mod k
                ans += get_valid_pos(lst,min(lst2,i - BUCK * k) - 1,i,k);
            }
        }
    }

    printf("%lld\n",ans);

    return 0;
}
