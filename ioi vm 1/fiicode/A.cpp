#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int t,n;
int x;
int a[100005];
int b[100005];

int main(){

    cin >> t;

    while(t--){
        cin >> n >> x;

        for(int i = 1;i <= n;i++){
            cin >> a[i];
            if(a[i] > (x ^ a[i])){
                a[i] ^= x;
            }
        }
        for(int i = 1;i <= n;i++){
            cin >> b[i];
            if(b[i] > (x ^ b[i])){
                b[i] ^= x;
            }
        }

        sort(a + 1,a + 1 + n);
        sort(b + 1,b + 1 + n);

        bool ok = true;

        for(int i = 1;i <= n;i++){
            ok &= (a[i] == b[i]);
        }

        cout << (ok ? "Yes\n":"No\n"); 
    }

    return 0;
}
