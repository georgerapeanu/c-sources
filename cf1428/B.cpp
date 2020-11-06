#include <bits/stdc++.h>

using namespace std;

int t;
int n;
string s;

int main(){

    cin >> t;

    while(t--){
        cin >> n;
        cin >> s;
        int ans = 0;
        bool fullclock = true;
        bool fullnoclock = true;
        for(int i = 0;i < n;i++){
            fullclock &= (s[i] != '<');
            fullnoclock &= (s[i] != '>');
        }
        for(int i = 0;i < n;i++){
            if(s[(i + n - 1) % n] == '-' || s[i] == '-' || fullclock || fullnoclock){
                ans++;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}
