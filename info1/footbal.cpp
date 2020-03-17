#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

bool solve(vector<int> &in,int k) {
    int sum = 0;
    int ma = 0;

    for(auto it:in) {
        ma = max(ma,it);
        sum ^= it;
    }

    k = min(k,ma);
    sum &= 1;

    if(sum) {
        return sum;
    }

    if(k == 1) {
        return sum;
    }

    k /= 2;

    for(auto &it:in) {
        it /= 2;
    }

    return solve(in,k);
}

int main() {
    int t;
    scanf("%d",&t);

    while(t--) {
        int n,k;
        scanf("%d %d",&n,&k);
        vector<int> v;
        while(n--) {
            int val;
            scanf("%d",&val);
            v.push_back(val);
        }
        printf("%d",solve(v,k));
    }

    return 0;
}
