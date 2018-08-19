#include <iostream>
#include <deque>

using namespace std;

int N;
int A[200005];
long long rez = 0;

int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> A[i];
    }

    A[0] = -1;
    for(int i = 1;i <= N;i++){
        if(A[i] > A[i - 1] + 1){
            cout << -1;
            return 0;
        }
        else if(A[i] < A[i - 1] + 1){
            rez += A[i];
        }
        else{
            rez += (i != 1);
        }
    }
    cout << rez;
    return 0;
}
