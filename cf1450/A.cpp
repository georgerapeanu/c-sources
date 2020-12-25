#include <bits/stdc++.h>

using namespace std;

int main(){
    int t;
    int n;
    string s;

    cin >> t;

    while(t--){
        cin >> n;
        cin >> s;
        sort(s.begin(),s.end());
        cout << s << "\n";
    }

    return 0;
}
