#include <iostream>

using namespace std;

int main(){
    int t;

    cin >> t;

    while(t--){
        int n;
        string s;
        cin >> n >> s;
        if(n == 2 && s[0] >= s[1]){
            cout << "NO\n";
        }
        else{
            cout << "YES\n2\n";
            cout << s[0] << " " << s.substr(1) << "\n";
        }
    }

    return 0;
}
