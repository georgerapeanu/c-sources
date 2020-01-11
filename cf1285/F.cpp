#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> d[100005];

bool have[100005];

bool comp[100005];
int mobius[100005];

int fr[100005];

int gcd(int a,int b) {
    if(!b)return a;
    return gcd(b,a % b);
}

int main() {

    for(int i = 1; i <= 100000; i++) {
        mobius[i] = 1;
    }

    for(int i = 1; i <= 100000; i++) {
        for(int j = i; j <= 100000; j += i) {
            d[j].push_back(i);
        }
        if(i == 1) {
            continue;
        }
        for(long long j = 1LL * i * i; j <= 100000; j += 1LL * i * i) {
            mobius[j] = 0;
        }
    }

    for(int i = 2; i <= 100000; i++) {
        if(comp[i] == false) {
            mobius[i] = -1;
        }
        for(int j = i; j <= 100000; j += i) {
            if(j != i)comp[j] = true;
            if(j > i && comp[i] == false) {
                mobius[j] *= mobius[i];
            }
        }
    }

    scanf("%d",&n);

    long long ans = 0;

    for(int i = 1; i <= n; i++) {
        int val;
        scanf("%d",&val);
        ans = max(1LL * val,ans);
        have[val] = true;
    }

    for(int g = 1; g <= 100000; g++) {
        vector<int> stuff;
        for(int i = g; i <= 100000; i += g) {
            if(have[i]) {
                stuff.push_back(i / g);
            }
        }
        if(stuff.size() < 2) {
            continue;
        }

        sort(stuff.begin(),stuff.end(),greater<int>());

        int pos = -1;

        for(int i = 0; i < (int)stuff.size(); i++) {

            long long cnt_cop = 0;

            for(auto it:d[stuff[i]]) {
                cnt_cop += mobius[it] * fr[it];
                fr[it]++;
            }
            while(pos >= 0 && cnt_cop > 0) {
                int gg = gcd(stuff[pos],stuff[i]);
                ans = max(ans,(1LL * stuff[pos] * stuff[i] / gg) * g);
                cnt_cop -= (gg == 1);
                for(auto it:d[stuff[pos]]) {
                    fr[it]--;
                }
                pos--;
            }
            stuff[++pos] = stuff[i];
        }

        for(int i = 0; i <= pos; i++) {
            for(auto it:d[stuff[i]]) {
                fr[it]--;
            }
        }
    }

    printf("%lld\n",ans);

    return 0;
}
