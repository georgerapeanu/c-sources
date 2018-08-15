#include <iostream>

using namespace std;

int N,A,B;
bool sw;
string S[1005];

int main(){

    cin >> N >> A >> B;
    if(A > 1 && B > 1){
        cout << "NO";
        return 0;
    }
    if(N == 1 && A == 1 && B == 1){
        cout << "YES\n0";
        return 0;
    }
    if(N <= 3 && A == 1 && B == 1){
        cout << "NO";
        return 0;
    }

    cout << "YES\n";

    for(int i = 0;i < N;i++){
        S[i].resize(N);
        for(auto &it:S[i]){
            it = '0';
        }
    }

    if(A == 1){
        sw = 1;
        swap(A,B);
    }

    for(int i = 0;i < N - A;i++){
        S[i][i + 1] = '1';
        S[i + 1][i] = '1';
    }

    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            S[i][j] = '0' + ((S[i][j] - '0') ^ (i == j ? 0 : sw));
        }
        cout << S[i] << "\n";
    }

    return 0;
}
