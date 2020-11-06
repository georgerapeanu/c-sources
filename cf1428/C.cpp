#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;

    cin >> t;

    while(t--){
        int cnt = 0;
        string s;
        cin >> s;

        for(auto it:s){
            if(it == 'A' || cnt == 0){
                cnt++;
            }
            else{
                cnt--;
            }
        }

        cout << cnt << "\n";
    }

    return 0;
}
