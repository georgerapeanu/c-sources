#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream f("hacker.in");
ofstream g("hacker.out");

const int MOD = 666013;

int solve(const string &s,int k){
    int ans = 1;
    for(auto it:s){
        if(it == '?'){
            ans = 1LL * ans * k % MOD;
        }
    }
    
    for(int pref = 0;pref < (int)s.size() - 1 - pref;pref++){
        string tmp;
        bool ok = true;
        for(int i = 0;i <= pref;i++){
            if(s[i] == '?'){
                tmp = tmp + s[(int)s.size() - 1 - pref + i];
            }
            else if(s[(int)s.size() - 1 - pref + i] == '?'){
                tmp = tmp + s[i];
            }
            else if(s[i] == s[(int)s.size() - 1 - pref + i]){
                tmp = tmp + s[i];
            }
            else{
                ok = false;
                break;
            }
        }
        
        int weight = 1;

        for(int i = pref + 1;i < (int)s.size() - 1 - pref;i++){
            if(s[i] == '?'){
                weight = 1LL * weight * k % MOD;
            }
        }

        if(ok == true){
            ans = (((ans - 1LL * weight * solve(tmp,k)) % MOD) + MOD) % MOD;
        }
    }
    return ans;
}

int main(){

    int n,k;
    string s;

    f >> n >> k;
    f >> s;

    g << solve(s,k);
    
    f.close();
    g.close();

    return 0;
}
