#include <bits/stdc++.h>

using namespace std;

int n;
string s;

long long get_cost(int len){
    if(len == 0){
        return 0;
    }
    return (1LL << len);
}

int solve(string s){
    long long cost = 0;
    int j = 0;
    int ans = 0;

    vector<int> l(s.size(),0);
    vector<int> r(s.size(),0);

    for(int i = (int)s.size() - 1;i >= 0;i--){
        r[i] = (s[i] == '1') * (i + 1 < (int)s.size() ? r[i + 1] + 1:1);
    }

    for(int i = 0;i < (int)s.size();i++){
        l[i] = (s[i] == '1') * (i > 0 ? l[i - 1] + 1:1);
    }

    for(int i = 0;i < (int)s.size();i++){
        if(j < i - 1){
            j = i - 1;
            cost = 0;
        }

        while(j + 1 < (int)s.size() && cost <= n){
            j++;
            if(s[j] == '0'){
                ;
            }
            else{
                cost += get_cost(min(l[j],j - i + 1)) - get_cost(min(l[j - 1],j - i));
            }
        }
        if(cost <= n){
            ans = max(ans,j - i + 1);
        }
        else{
            ans = max(ans,j - i);
        }
        
        if(s[i] == '0'){
            ;
        }
        else{
            cost -= (get_cost(min(r[i],j - i + 1)) - get_cost(min(r[i + 1],j - i)));
        }
    }
    return ans;
}

int main(){

    cin >> s;
    cin >> n;

    int ans = 0;

    for(char c = 'a';c <= 'z';c++){
        string t = s;
        for(int i = 0;i < (int)s.size();i++){
            t[i] = (s[i] == c ? '0':'1');
        }
        ans = max(ans,solve(t));
    }

    cout << ans;

    return 0;
}
