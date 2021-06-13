#include <bits/stdc++.h>

using namespace std;

int t;
int a,b,d;

int main(){

    cin >> t;

    while(t--){
        cin >> a >> b >> d;
        if(a > b){
            swap(a,b);
        }

        cout << (b > 1LL * (d + 1) * a ? "NO\n":"YES\n");
    }


    return 0;
}
