#include <iostream>

using namespace std;

int main(){
    long long N,rez = 0;
    cin >> N;N--;
    for(long long p2 = 1,e = 1;p2 <= N;p2 *= 2,e++){
        rez += p2 * (N / p2 - N / (2 * p2));
    }
    cout << rez;
    return 0;
}
