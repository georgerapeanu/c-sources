#include <iostream>

using namespace std;

long long N,M,A,B;

int main(){
    cin >> N >> M >> A >> B;
    cout << min((N % M) * B,(M - (N % M)) * A);
    return 0;
}
