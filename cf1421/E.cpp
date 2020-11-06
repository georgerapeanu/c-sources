#include <bits/stdc++.h>

using namespace std;

int main(){

    int n;
    long long ans = -1e18;

    vector<pair<int,int>> v;

    cin >> n;

    vector<int> sgn(n,1);

    long long sum = 0;
    for(int i = 1;i <= n;i++){
        v.push_back({0,i - 1});
        cin >> v.back().first;
        sum += v.back().first;
    }

    if(n == 1){
        cout << v.back().first << "\n";
        return 0;
    }

    sort(v.begin(),v.end());

    int lst = 1;

    for(int i = ((1 - n) % 3 + 3) % 3;i <= n;i += 3){
        while(lst <= i){
            sum -= 2 * v[lst - 1].first;
            sgn[v[lst - 1].second] *= -1;
            lst++;
        }
        if(abs(n - 2 * i) == 1){
            bool ok = false;
            for(int i = 0;i < (int)v.size() - 1;i++){
                ok |= (sgn[i] == sgn[i + 1]);
            }
            if(ok){
                ans = max(ans,sum);
            }
            else{
                ans = max(ans,sum + 2 * v[i - 1].first - 2 * v[i].first);
            }
        }
        else{
            ans = max(ans,sum);
        }
    }
   
    cout << ans << "\n";

    return 0;
}
