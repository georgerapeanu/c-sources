#include <bits/stdc++.h>

using namespace std;

int gcd(int a,int b){
    if(b == 0){
        return a;
    }
    return gcd(b,a % b);
}


int main(){
    
    int t;

    cin >> t;

    while(t--){
        string s,t;
        cin >> s >> t;

        bool ok = true;

        int len = (int)s.size() * (int)t.size() / gcd(s.size(),t.size());

        for(int i = 0;i < len;i++){
            ok &= (s[i % (int)s.size()] == t[i % (int)t.size()]);
        }

        if(ok){
            for(int i = 0;i < len;i++){
                cout << s[i % (int)s.size()];
            }
            cout << "\n";
        }else{
            cout << "-1\n";
        }
    }

    return 0;
}
