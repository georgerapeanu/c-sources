#include <bits/stdc++.h>

using namespace std;

int query(int l,int r){
    int ans;

    cout << "? " << l << " " << r << endl;

    cin >> ans;
    
    return ans;
}

int main(){

    int n,q;

    cin >> n >> q;

    vector<int> v = {};

    string s = string(n,' ');

    for(int i = 1;i <= n;i++){
        if((int)v.size() < 1){
            v.push_back(i);
        }
        else if(query(v.back(),i) == 1){
            s[v.back() - 1] = '(';
            s[i - 1] = ')';
            v.pop_back();
        }
        else{
            v.push_back(i);
        }
    }

    for(int i = 0;i < (int)v.size();i++){
        if(2 * i < (int)v.size()){
            s[v[i] - 1] = ')';
        }
        else{
            s[v[i] - 1] = '(';
        }
    }

    cout << "! " <<  s << endl;

    return 0;
}
