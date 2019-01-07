#include <iostream>

using namespace std;

int main(){
    string a;

    cin >> a;

    for(int i = 0;i < 5;i++){
        string b;
        cin >> b;
        if(a[0] == b[0] || a[1] == b[1]){
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
