#include <iostream>

using namespace std;

int X,Y,L,R,rez;

int gcd(int x,int y){
    if(!y)return x;
    return gcd(y,x % y);
}

int main(){
    cin >> L >> R >> X >> Y;
    if(Y % X != 0){
        cout << 0;
        return 0;
    }
    R /= X;
    L = (L / X) + (L % X != 0);
    Y /= X;
    for(int a = 1;1LL * a * a <= Y;a++){
        if(Y % a != 0){
            continue;
        }
        int b = Y / a;
        if(gcd(a,b) == 1 && L <= a && a <= R && L <= b && b <= R){
            rez += (a == b ? 1 : 2);
        }
    }

    cout << rez;

    return 0;
}
