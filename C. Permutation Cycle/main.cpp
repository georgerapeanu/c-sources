#include <iostream>

using namespace std;
int N,A,B;
void baga(int a,int b){
    int last = 0;
    while(a--){
        for(int i = 1;i < A;i++){
            cout << last + i + 1 << " ";
        }
        cout << last + 1 << " ";
        last += A;
    }
    while(b--){
        for(int i = 1;i < B;i++){
            cout << last + i + 1 << " ";
        }
        cout << last + 1 << " ";
        last += B;
    }
}
int main(){
    cin >> N >> A >> B;
    for(int i = 0;i * A <= N;i++){
        if((N - i * A) % B == 0){
            baga(i,(N - i * A) / B);
            return 0;
        }
    }
    cout << -1;
    return 0;
}
