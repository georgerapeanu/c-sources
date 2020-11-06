#include <bits/stdc++.h>

using namespace std;

int main() {

    int n,m;

    cin >> n;

    vector<int> prices(n,0);
    vector<long long> pref_sum(n,0);

    for(auto &itr:prices) {
        cin >> itr;
    }

    for(int i = 0;i < n;i++) {
        pref_sum[i] = prices[i] + (i > 0 ? pref_sum[i - 1]:0);
    }

    cin >> m;
    cout << m << endl;

    while(m--){
        int id, t;

        cin >> id >> t;

        pair<long long,int> best = {1e18,0};

        for(int i = 0;i + t - 1 < n;i++){
            best = min(best,{pref_sum[i + t - 1] - (i == 0 ? 0:pref_sum[i - 1]),i});
        }

        cout << id << " " << best.second << endl;
    }

    return 0;
}
