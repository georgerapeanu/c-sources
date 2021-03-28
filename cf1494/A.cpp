#include <bits/stdc++.h>

using namespace std;

int t;
string s;
int value[300];

int main(){

    cin >> t;

    while(t--){
        cin >> s;

        bool ok_overall = false;

        for(value['A'] = -1;value['A'] <= 1;value['A'] += 2){
            for(value['B'] = -1;value['B'] <= 1;value['B'] += 2){
                for(value['C'] = -1;value['C'] <= 1;value['C'] += 2){
                    int sum = 0;
                    bool ok = true;

                    for(auto it:s){
                        sum += value[it];
                        ok &= (sum >= 0);
                    }
                    ok &= (sum == 0);
                    ok_overall |= ok;
                }
            }
        }

        printf(ok_overall ? "YES\n":"NO\n");
    }
    

    return 0;
}
