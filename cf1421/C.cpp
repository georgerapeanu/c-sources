#include <bits/stdc++.h>

using namespace std;

int main(){
    
    string s;
    cin >> s;

    cout << "3\n";
    cout << "R 2\n";
    cout << "L " << (int)s.size() << "\n";
    cout << "L " << (int)s.size() - 1 << "\n";

    return 0;
}
