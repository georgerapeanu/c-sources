#include <bits/stdc++.h>

using namespace std;

int t;

int main(){

    cin >> t;

    while(t--){
        int cnt_1 = 0,cnt_2 = 0;
        int n;

        cin >> n;

        for(int i = 1;i <= n;i++){
            int val;
            cin >> val;
            cnt_1 += (val == 1);
            cnt_2 += (val == 2);
        }

        if(cnt_1 % 2 == 1){
            cout << "NO\n";
            continue;
        }
        if(cnt_1 > 0 && cnt_2 % 2 == 1){
            cnt_1 -= 2;
            cnt_2++;
        }
        if(cnt_2 % 2 == 0){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }

    return 0;
}
