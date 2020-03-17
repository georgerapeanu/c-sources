#include <iostream>

using namespace std;

int main(){
    int n,k;
    int ans = 0;

    cin >> n >> k;

    while(n){
        n /= k;
        ans++;
    }

    cout << ans << "\n";

    return 0;
}
