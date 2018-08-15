#include <iostream>

using namespace std;

int N;
int A[200005];
int l,r,xo;
long long rez;

int main(){

    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> A[i];
    }

    l = 1;
    xo = 0;

    for(int r = 1;r <= N;r++){
        while(xo & A[r]){
            xo ^= A[l];
            l++;
        }
        xo ^= A[r];
        rez += r - l + 1;
    }

    cout << rez;

    return 0;
}
