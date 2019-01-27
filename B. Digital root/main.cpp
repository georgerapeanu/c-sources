#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++){
        long long k,x;
        cin >> k >> x;
        cout << 9 * (k - 1) + x << "\n";
    }
    return 0;
}
