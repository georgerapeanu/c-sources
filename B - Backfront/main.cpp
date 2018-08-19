#include <iostream>

using namespace std;
int P[200005];
int sz[200005];
int N;
int rez;
int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> P[i];
        sz[P[i]] = 1 + sz[P[i]  - 1];
        rez = max(rez,sz[P[i]]);
    }
    cout << N - rez;
    return 0;
}
