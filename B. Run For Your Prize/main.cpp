#include <iostream>

using namespace std;
int A[100005];
int rez = 1 << 30,N;
int main()
{
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> A[i];
    }
    A[N + 1] = 1e6;
    for(int i = 0;i <= N;i++){
        rez = min(rez,max(A[i] - 1,int(1e6) - A[i + 1]));
    }
    cout << rez;
    return 0;
}
