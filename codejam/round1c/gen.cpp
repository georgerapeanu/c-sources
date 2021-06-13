#include <bits/stdc++.h>

using namespace std;

string int_to_bin(int a){
    if(a == 0){
        return "0";
    }
    string ans = "";

    while(a){
        ans += (a % 2) + '0';
        a /= 2;
    }

    reverse(ans.begin(),ans.end());
    return ans;
}

int main(){
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    cout << "1\n";

    int a = (gen() & ((1 << 8) - 1));
    int b = (gen() & ((1 << 8) - 1));
    
    cout << int_to_bin(a) << " ";
    cout << int_to_bin(b) << " ";


    return 0;
}
