#include <iostream>
#include <algorithm>
using namespace std;
int N,K;
int x;
int rez;
int main()
{
    cin >> N >> K;
    while(N--){
        cin >> x;
        if(K % x == 0){
            rez = max(rez,x);
        }
    }
    cout << K / rez;
    return 0;
}
