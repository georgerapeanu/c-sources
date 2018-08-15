#include <iostream>

using namespace std;

int W,E,N,rez = 1 << 30;
string S;

int main(){
    cin >> N;
    cin >> S;
    for(auto it:S){
        E += (it == 'E');
    }
    for(auto it:S){
        E -= (it == 'E');
        rez = min(rez,E + W);
        W += (it == 'W');
    }
    cout << rez;
    return 0;
}
