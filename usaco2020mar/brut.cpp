#include <bits/stdc++.h>

using namespace std;

vector<long long> lcm[7505];
int n;

long long gcd(long long a,long long b) {
    if(b == 0) {
        return a;
    }
    return gcd(b,a % b);
}

long long get_lcm(long long a,long long b) {
    return a * b / gcd(a,b);
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        lcm[i].push_back(i);
        for(int j = 1; j < i; j++) {
            for(auto it:lcm[j]) {
                lcm[i].push_back(get_lcm(it,i - j));
            }
        }
        sort(lcm[i].begin(),lcm[i].end());
        lcm[i].resize(unique(lcm[i].begin(),lcm[i].end()) - lcm[i].begin());
        printf("%d %d\n",i,(int)lcm[i].size());
    }

    return 0;
}
