#include <iostream>

using namespace std;

int main(){
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    int t;
    cin >> t;
    while(t--){
        int ang;
        cin >> ang;
        for(int n = 3;n <= 360;n++){
            if((n * ang) % 180 == 0 && (n * ang) / 180 <= n - 2){
                cout << n << "\n";
                break;
            }
        }
    }    
    return 0;
}
