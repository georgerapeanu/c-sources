#include <bits/stdc++.h>

using namespace std;

int main(){

    int a,b;
    cin >> a >> b;
    a--;
    b--;
    if(a % 2 == 1 || b % 2 == 1){
        cout << "A";
    }else{
        cout << "P";
    }

    return 0;
}
