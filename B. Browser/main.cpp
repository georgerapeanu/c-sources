#include <iostream>
#include <algorithm>

using namespace std;
int N,pos,l,r;
int main()
{
    cin >> N >> pos >> l >> r;
    if(l == 1){
        if(r != N){
            cout << abs(r - pos) + 1;
        }
        else{
            cout << 0;
        }
    }
    else{
        if(r != N){
            cout << 2 + abs(r - l) + min(abs(pos - l),abs(r - pos));
        }
        else {
            cout << abs(pos - l) + 1;
        }
    }
    return 0;
}
