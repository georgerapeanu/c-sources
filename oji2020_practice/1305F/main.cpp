#include <cstdio>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

const int NMAX = 2e5;

int n;
long long val[NMAX + 5];

int solve(long long v){
    if(v == 0){
        return 1e9;
    }
    vector<long long> fact;

    for(int i = 2;1LL * i * i <= v;i++){
        if(v % i == 0){
            fact.push_back(i);
            while(v % i == 0){
                v /= i;
            }
        }
    }

    if(v != 1){
        fact.push_back(v);
    }

    long long ans = 1e9;

    for(auto it:fact){
        long long tmp = 0;
        for(int i = 1;i <= n;i++){
            if(val[i] < it){
                tmp += it - val[i];
            }
            else{
                tmp += min(val[i] % it,it - (val[i] % it));
            }
        }
        ans = min(ans,tmp);
    }

    return int(ans);
}

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%lld",&val[i]);
    }

    int ans = n;

    for(int chestie = 0;chestie < 20;chestie++){
        int pos = gen() % n + 1;
        ans = min(ans,solve(val[pos] - 1));
        ans = min(ans,solve(val[pos]));
        ans = min(ans,solve(val[pos] + 1));
    }

    printf("%d\n",ans);

    return 0;
}
