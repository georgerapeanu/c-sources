#include <bits/stdc++.h>

using namespace std;

int get_phi(int value){
    
    int ans = value;

    for(int i = 2;1LL * i * i <= value;i++){
        if(value % i == 0){
            ans /= i;
            ans *= (i - 1);
            while(value % i == 0){
                value /= i;
            }
        }
    }
    if(value > 1){
        ans /= value;
        ans *= (value - 1);
        value = 1;
    }
    
    return ans;
}

const int NMAX = 1e5;

int n,m;
long long a[2 * NMAX + 5];

vector<int> mods;

int lgpow(int b,int e,int mod){
    int ans = 1;

    while(e){
        if(e & 1){
            ans = 1LL * ans * b % mod;
        }
        b = 1LL * b * b % mod;
        e >>= 1;
    }
    return ans;
}

int solve(int i,int h){
    if(mods[h] == 1){
        return 0;
    }
    if(i == 0){
        return 1;
    }
    return lgpow(a[i] % mods[h],solve(i - 1,h + 1),mods[h]);
}

int main(){

    scanf("%d %d",&n,&m);
    mods.push_back(m);

    while(mods.back() != 1){
        mods.push_back(get_phi(mods.back()));
    }

    for(int i = 1;i <= 2 * n;i++){
        scanf("%lld",&a[i]);
        printf("%d ",solve(i,0));
    }

    return 0;
}
