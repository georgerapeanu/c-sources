#include <bits/stdc++.h>

using namespace std;

vector<long long> mods = {(long long)(2e9+696969)};

long long get_phi(long long val) {
    long long phi = val;

    for(int d = 2; 1LL * d * d <= val; d++) {
        if(val % d == 0) {
            phi = phi / d * (d - 1);
            while(val % d == 0) {
                val /= d;
            }
        }
    }

    if(val != 1) {
        phi = phi / val * (val - 1);
    }

    return phi;
}

char c[int(1e5) + 5];
int ind = 1;

long long lgpow(long long b,long long e,long long mod) {
    long long p = 1;

    while(e) {
        if(e & 1) {
            p = p * b % mod;
        }
        b = b * b % mod;
        e >>= 1;
    }

    return p;
}

long long expr(int lvl);

long long num(int lvl) {
    long long ans = 0;

    if(c[ind] == '(') {
        ind++;
        ans = expr(lvl);
        ind++;
        return ans;
    }

    while('0' <= c[ind] && c[ind] <= '9') {
        ans = (ans * 10 + c[ind] - '0') % mods[lvl];
        ind++;
    }

    return ans;
}

long long fact(int lvl) {
    long long ans = num(lvl);

    if(c[ind] == '^') {
        ind++;
        ans = lgpow(ans,fact(min((int)mods.size() - 1,lvl + 1)),mods[lvl]);
    }

    return ans;
}

long long term(int lvl) {
    long long ans = fact(lvl);

    while(c[ind] == '*' || c[ind] == '/') {
        bool sgn = (c[ind] == '*');
        ind++;
        if(sgn == 1) {
            ans = ans * fact(lvl) % mods[lvl];
        }
        else {
            ans = ans * lgpow(fact(lvl),mods[min(lvl + 1,(int)mods.size() - 1)] - 1,mods[lvl]) % mods[lvl];
        }
    }

    return ans;
}

long long expr(int lvl) {
    long long ans = term(lvl);

    while(c[ind] == '+' || c[ind] == '-') {
        int sgn = (c[ind] == '+' ? 1:-1);
        ind++;
        ans = (ans + sgn * term(lvl)) % mods[lvl];
        if(ans < 0)ans += mods[lvl];
    }

    return ans;
}

int main() {

    for(int i = 0; i < (int)mods.size(); i++) {
        if(mods[i] != 1) {
            mods.push_back(get_phi(mods[i]));
        }
    }

    fscanf(stdin,"%s",c + 1);

    long long ans = expr(0);

    if(ans > 1e9) {
        ans -= mods[0];
    }

    printf("%lld\n",ans);

    return 0;
}
