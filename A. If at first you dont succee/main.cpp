#include <iostream>

using namespace std;

int N,A,B,C;

int main(){
    cin >> A >> B >> C >> N;
    if(C > min(A,B)){
        cout << -1;
        return 0;
    }
    int AUB = A + B - C;
    int fai = N - AUB;
    if(fai <= 0 || fai > N)cout << -1;
    else cout << fai;
    return 0;
}
