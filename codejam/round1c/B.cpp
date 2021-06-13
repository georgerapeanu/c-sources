#include <bits/stdc++.h>

using namespace std;

string _min(string a,string b){
    if(a == ""){
        return b;
    }
    if(b == ""){
        return a;
    }
    if(a.size() != b.size()){
        return (a.size() < b.size() ? a : b);
    }

    return a < b ? a:b;
}

int tests;
string s;

string ll_to_string(long long x){
    string ans = "";

    while(x){
        ans += (x % 10) + '0';
        x /= 10;
    }
    reverse(ans.begin(),ans.end());
    
    return ans;
}

string get_year(const string &s,long long x){
    string ans = "";
    int cnt = 0;
    while((ans == "" || _min(ans,s) == ans) || cnt < 2){
        ans += ll_to_string(x);
        x++;
        cnt++;
    }
    return ans;
}

void update_ans(string &ans,const string &s,string x){
    if(_min(s,x) != x){
        ans = _min(ans,x);
    }
}

int main(){

    cin >> tests;

    for(int test = 1;test <= tests;test++){
        cout << "Case #" << test << ": ";

        cin >> s;
        long long fst = 0;
        long long pw10 = 1;
        string ans = "";
        for(int k = 0;k < (int)s.size();k++){
            fst = fst * 10 + s[k] - '0';
            update_ans(ans,s,get_year(s,fst)); 
            update_ans(ans,s,get_year(s,fst + 1)); 
            update_ans(ans,s,get_year(s,pw10));
            for(int k = 0;k <= 18 && k < pw10;k++){
                update_ans(ans,s,get_year(s,pw10 - k));
            }
            pw10 *= 10LL;
        }

        cout << ans << "\n";
    }

    return 0;
}
