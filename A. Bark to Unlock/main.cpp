#include <iostream>

using namespace std;
string pass;
string a;
int N;
bool isF[280];
bool isS[280];
int main(){
    cin >> pass;
    cin >> N;
    while(N--){
        cin >> a;
        isF[a[0]] = 1;
        isS[a[1]] = 1;
        if(a == pass){
            cout << "YES";
            return 0;
        }
    }
    cout << (isS[pass[0]] + isF[pass[1]] == 2 ? "YES":"NO");
    return 0;
}
