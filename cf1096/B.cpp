#include <iostream>

using namespace std;

int main(){
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
   
    int n;
    string s;
    cin >> n;
    cin >> s;

    int a = 0,b = 0;
   
    while(s[0] == s[a]){
        a++;
    }

    while(s[n - 1] == s[n - 1 - b]){
        b++;
    }

    if(s[0] == s[n - 1]){
        cout << 1LL * (a + 1) * (b + 1) % 998244353;       
    }
    else{
        cout << a + b + 1;
    }
    return 0;
}
