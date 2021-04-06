#include <bits/stdc++.h>

using namespace std;

int main(){

    int n;
    cin >> n;
    
    for(int x = 2;x <= n;x++){
        long long tmp = 1;

        while(tmp < n){
            tmp *= x;
        }
        if(tmp == n){
            cout << x << endl;
            return 0;
        }
    }

    cout << 1;

    return 0;
}
