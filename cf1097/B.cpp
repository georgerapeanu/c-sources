#include <iostream>

using namespace std;

int n;
int a[20];

void btr(int pas,int sum){
    if(pas > n){
        if(sum % 360 == 0){
          cout << "YES\n";
          exit(0);
        }
        return ;
    }
    btr(pas + 1,sum - a[pas]);
    btr(pas + 1,sum + a[pas]);
}

int main(){

    cin >> n;

    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }

    btr(1,0);

    cout << "NO\n";

    return 0;
}
