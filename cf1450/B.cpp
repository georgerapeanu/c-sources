#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
    int n;
    int k;
    vector<pair<int,int> > v;

    cin >> t;

    while(t--){
        cin >> n >> k;
        v = vector<pair<int,int> > (n,make_pair(0,0));
        for(auto &it:v){
            cin >> it.first >> it.second;
        }

        bool ok = false;

        for(int i = 0;i < n && ok == false;i++){
            bool local_ok = true;
            for(auto it:v){
                local_ok &= (abs(it.first - v[i].first) + abs(it.second - v[i].second) <= k);
            }
            ok |= local_ok;
        }
        cout << (ok ? 1:-1) << "\n";
    }

    return 0;
}
