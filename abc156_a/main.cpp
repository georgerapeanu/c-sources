#include <iostream>

using namespace std;

int main(){
    int n,r;
    cin >> n >> r;
    if(n >= 10){cout << r;}
    else{
        cout << r + 100 * (10 - n);
    }
    return 0;
}
