#include <bits/stdc++.h>

using namespace std;

int main() {

    int n,m;

    cin >> n;

    vector<int> prices(n,0);

    for(auto &itr:prices) {
        cin >> itr;
    }

    cin >> m;
    cout << m << endl;

    while(m--){
        int id, t;
        int p, l,r;

        cin >> id >> p >> l >> r;

        pair<int,int> best = {1e9,0};

        for(int i = l;i <= r;i++){
            best = min(best,{prices[i],i});
        }

        cout << id << " " << best.second << " " << p << endl;
    }

    return 0;
}
