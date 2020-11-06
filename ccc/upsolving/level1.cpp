#include <bits/stdc++.h>

using namespace std;

int main() {

    int n;

    cin >> n;

    vector<int> prices(n,0);

    for(auto &itr:prices) {
        cin >> itr;
    }

    pair<int,int> best = {1e9,0};

    for(int i = 0;i < (int)prices.size();i++) {
        best = min(best,make_pair(prices[i],i));
    }

    printf("%d\n",best.second);
    
    return 0;
}
