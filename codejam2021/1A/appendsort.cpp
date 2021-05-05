#include <bits/stdc++.h>

using namespace std;

int t;
int n;
string s[105];

int main(){
    
    cin >> t;
    
    for(int h = 1;h <= t;h++){
        int ans = 0;

        cin >> n;
        
        for(int i = 1;i <= n;i++){
            cin >> s[i];
            s[i] = " " + s[i];
        }
        
        for(int i = 2;i <= n;i++){
            if(s[i].size() > s[i - 1].size()){
                continue;
            }
            int wh = 0;
            for(int j = 1;j < (int)s[i].size();j++){
                if(s[i - 1][j] != s[i][j]){
                    if(s[i - 1][j] < s[i][j]){
                        wh = 1;
                        break;
                    }else{
                        wh = 2;
                        break;
                    }
                }
            }
            if(wh == 1){
                while(s[i].size() < s[i - 1].size()){
                    s[i] += "0";
                    ans++;
                }
            }else if(wh == 2){
                while(s[i].size() <= s[i - 1].size()){
                    s[i] += "0";
                    ans++;
                }
            }else{
                int lst = -1;
                for(int j = (int)s[i].size();j < (int)s[i - 1].size();j++){
                    if(s[i - 1][j] != '9'){
                        lst = j;
                    }
                }
                if(lst == -1){
                    while(s[i].size() <= s[i - 1].size()){
                        s[i] += "0";
                        ans++;
                    }
                }else{
                    ans += s[i - 1].size() - s[i].size();
                    s[i] = s[i - 1];
                    s[i][lst]++;
                    for(int j = lst + 1;j < (int)s[i].size();j++){
                        s[i][j] = '0';
                    }
                }
            }
        }
        cout << "Case #" << h << ": " << ans << endl;
    }
        
    return 0;
}
