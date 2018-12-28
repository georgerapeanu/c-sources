#include <iostream>

using namespace std;

int main(){
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        int l,r;
        cin >> l >> r;
        cout << l << " " << 2 * l << "\n";
    }
    return 0;
}
