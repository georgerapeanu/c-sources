#include <bits/stdc++.h>

using namespace std;

int n;
string s;

int main() {

    cin >> n;
    cin >> s;

    int sum = 0;
    int mi_sum = 0,cnt_sum = 1;

    for(auto it:s){
        if(it == '('){
            sum++;
        }
        else{
            sum--;
        }
        if(mi_sum > sum){
            mi_sum = sum;
            cnt_sum = 1;
        }
        else if(mi_sum == sum){
            cnt_sum++;
        }
    }

    if(sum != 0 || mi_sum < -1){
        cout << "No" << "\n";
    }
    else{
        cout << "Yes" << "\n";
    }

    return 0;
}
