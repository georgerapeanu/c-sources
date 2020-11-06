#include "biscuits.h"
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int maxK = 128;

long long s[64];
long long X;

unordered_map<long long,long long> ans;

long long solve(long long n){
    if(n <= 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    if(ans.count(n) == 0){
        int bit = 62;
        while(((n - 1) >> bit) == 0){
            bit--;
        }
        ans[n] =  solve(1LL << bit) + solve(min(n,1 + s[bit] / X) - (1LL << bit));
    }
    return ans[n];
}

long long count_tastiness(long long x, vector<long long> a) {
   
    ans.clear();

    X = x;

    for(int i = 0;i < 61;i++){
        s[i] = ((i < (int)a.size() ? a[i]:0) << i) + (i > 0 ? s[i - 1]:0);
    }

	return solve(1LL << 61);
}

