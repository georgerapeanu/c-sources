#include <bits/stdc++.h>

using namespace std;

int t;
int n;
long long k;

int main(){

    cin >> t;

    while(t--){
        cin >> n >> k;
        if(n <= 61 && k > (1LL << (n - 1))){
            cout << -1 << "\n"; 
            continue;
        }
        int pos = 0;

        while(pos < n){
            for(int i = pos + 1;i <= n;i++){
                if(n - i >= 61 || k <= (1LL << max(0,n - i - 1))){
                    for(int value = i;value > pos;value--){
                       cout << value << " "; 
                    }
                    pos = i;
                    break;
                }else{
                    k -= (1LL << max(0,n - i - 1));
                }
            }
        }
        cout << "\n";
    }

    return 0;
}
