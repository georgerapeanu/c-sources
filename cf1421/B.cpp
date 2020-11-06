#include <bits/stdc++.h>

using namespace std;

int main(){

    int t,n;

    cin >> t;
    string s[205];

    while(t--){
        cin >> n;
        for(int i = 1;i <= n;i++){
            cin >> s[i];
            s[i] = " " + s[i];
        }

        int fr0 = (s[n][n - 2] == '0') + (s[n - 1][n - 1] == '0') + (s[n - 2][n] == '0');
        int fr1 = 3 - fr0;

        vector<pair<int,int> > ans;

        if(fr0 == 3){
            if(s[n][n - 1] == '0')ans.push_back({n,n - 1});
            if(s[n - 1][n] == '0')ans.push_back({n - 1,n});
        }
        else if(fr1 == 3){
            if(s[n][n - 1] == '1')ans.push_back({n,n - 1});
            if(s[n - 1][n] == '1')ans.push_back({n - 1,n});
        }
        else if(fr0 == 1){
            if(s[n][n - 1] == s[n - 1][n]){
                if(s[n][n - 1] == '0'){
                    if(s[n - 2][n] == '0')ans.push_back({n - 2,n});
                    if(s[n - 1][n - 1] == '0')ans.push_back({n - 1,n - 1});
                    if(s[n][n - 2] == '0')ans.push_back({n,n - 2});
                }
                else{
                    if(s[n - 2][n] == '1')ans.push_back({n - 2,n});
                    if(s[n - 1][n - 1] == '1')ans.push_back({n - 1,n - 1});
                    if(s[n][n - 2] == '1')ans.push_back({n,n - 2});
                }
            }
            else{
                if(s[n - 2][n] == '0')ans.push_back({n - 2,n});
                if(s[n - 1][n - 1] == '0')ans.push_back({n - 1,n - 1});
                if(s[n][n - 2] == '0')ans.push_back({n,n - 2});
                if(s[n][n - 1] == '1')ans.push_back({n,n - 1});
                if(s[n - 1][n] == '1')ans.push_back({n - 1,n});
            }
        }
        else{
            if(s[n][n - 1] == s[n - 1][n]){
                if(s[n][n - 1] == '0'){
                    if(s[n - 2][n] == '0')ans.push_back({n - 2,n});
                    if(s[n - 1][n - 1] == '0')ans.push_back({n - 1,n - 1});
                    if(s[n][n - 2] == '0')ans.push_back({n,n - 2});
                }
                else{
                    if(s[n - 2][n] == '1')ans.push_back({n - 2,n});
                    if(s[n - 1][n - 1] == '1')ans.push_back({n - 1,n - 1});
                    if(s[n][n - 2] == '1')ans.push_back({n,n - 2});
                }
            }
            else{
                if(s[n - 2][n] == '1')ans.push_back({n - 2,n});
                if(s[n - 1][n - 1] == '1')ans.push_back({n - 1,n - 1});
                if(s[n][n - 2] == '1')ans.push_back({n,n - 2});
                if(s[n][n - 1] == '0')ans.push_back({n,n - 1});
                if(s[n - 1][n] == '0')ans.push_back({n - 1,n});
            
            }
        }

        printf("%d\n",(int)ans.size());

        for(auto it:ans)printf("%d %d\n",it.first,it.second);
    }

    return 0;
}
