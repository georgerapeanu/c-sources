#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int get_upper_bound(int n){
    int k = n / 2;
    return k * (n - k - 1);
}

int main(){
    int n;
    int m;

    cin >> n >> m;

    if(get_upper_bound(n) < m){
        cout << -1;
        return 0;
    }

    if(n < 3){
        for(int i = 1;i <= n;i++){
            cout << i << " ";
        }
        return 0;
    }

    int tmp = 0;

    while(get_upper_bound(tmp + 1) < m){
        tmp++;
    }

    int delta = (m - get_upper_bound(tmp));

    for(int i = 1;i <= tmp;i++){
        cout << i << " ";
    }

    cout << 2 * tmp - 2 * delta + 1 << " ";

    int lst = 2 * tmp - 2 * delta + 1;

    for(int i = tmp + 2;i <= n;i++){
        cout << int(1e9) - (n - i) * (lst + 1) << " ";
    }

    return 0;
}
