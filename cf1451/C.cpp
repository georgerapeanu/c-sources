#include <bits/stdc++.h>

using namespace std;

int t;
int n,k;
int fr[30];
string a,b;

int main(){

    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);

    cin >> t;

    while(t--){
        cin >> n >> k;
        cin >> a >> b;

        for(int i = 0;i < 30;i++){
            fr[i] = 0;
        }

        for(auto it:a){
            fr[it - 'a']++;
        }
        for(auto it:b){
            fr[it - 'a']--;
        }

        bool ok = true;
        int bonus = 0;
        for(int i = 0;i < 30;i++){
            bonus += fr[i];
            if(bonus < 0){
                ok = false;
                break;
            }
            if(fr[i] % k != 0){
                ok = false;
                break;
            }
        }
        if(ok){
            printf("Yes\n");
        }
        else{
            printf("No\n");
        }

    }

    return 0;
}
