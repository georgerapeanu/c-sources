#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;
        vector<int> v(n + 1,0);
        string ans(n,'0');
        vector<int> wh(n + 1,0);
        vector<int> l(n + 1,0);
        vector<int> r(n + 1,0);

        for(int i = 1;i <= n;i++){
            cin >> v[i];
        }

        vector<int> st = {0};

        for(int i = 1;i <= n;i++){
            while(v[st.back()] >= v[i]){
                r[st.back()] = i;
                st.pop_back();
            }
            l[i] = st.back();
            st.push_back(i);
        }
        for(auto it:st){
            r[it] = n + 1;
        }

        for(int i = 1;i <= n;i++){
            wh[v[i]] = max(wh[v[i]],r[i] - l[i] - 1);
        }
        
        int mi = n + 1;

        for(int i = 1;i <= n;i++){
            mi = min(mi,wh[i]);
            if(mi >= n - i + 1){
                ans[n - i + 1 - 1] = '1';
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
