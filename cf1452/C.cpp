#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
    string s;

    cin >> t;

    while(t--){
        cin >> s;

        vector<int> tmp[2];

        int ans = 0;
        for(auto it:s){
            if(it == '('){
                tmp[0].push_back(it);
            }
            else if(it == '['){
                tmp[1].push_back(it);
            }
            else if(it == ')'){
                if(tmp[0].empty() || tmp[0].back() != '('){
                    tmp[0].push_back(it);
                }
                else{
                    tmp[0].pop_back();
                    ans++;
                }
            }
            else{
                if(tmp[1].empty() || tmp[1].back() != '['){
                    tmp[1].push_back(it);
                }
                else{
                    tmp[1].pop_back();
                    ans++;
                }
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
