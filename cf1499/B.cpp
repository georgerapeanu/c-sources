#include <bits/stdc++.h>

using namespace std;

int t;
string s;
bool ok_l[1005];
bool ok_r[1005];

int main(){

    cin >> t;

    while(t--){
        cin >> s;

        s = " " + s;
        
        ok_l[0] = true;
        for(int i = 1;i < (int)s.size();i++){
            ok_l[i] = false;
            if(s[i] == '0'){
                ok_l[i] = ok_l[i - 1];
            }else if(s[i - 1] != '1'){
                ok_l[i] = (i < 2 ? true:ok_l[i - 2]);
            }
        }

        ok_r[(int)s.size()] = true;

        for(int i = (int)s.size() - 1;i >= 1;i--){
            ok_r[i] = false;
            if(s[i] == '1'){
                ok_r[i] = ok_r[i + 1];
            }else if(i == (int)s.size() - 1 || s[i + 1] != '0'){
                ok_r[i] = (i + 2 < (int)s.size() - 1 ? ok_r[i + 2]:true);
            }
        }
        
        bool ok = false;

        for(int i = 0;i < (int)s.size();i++){
            if(ok_l[i] == true && ok_r[i + 1] == true){
                ok = true;
                break;
            }
        }

        printf(ok ? "YES\n":"NO\n");
    }


    return 0;
}
