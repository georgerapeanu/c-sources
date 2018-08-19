#include <iostream>
#include <cstdio>
using namespace std;
int V[105];
int P[105];
int A[105];
int N;
int main()
{
    freopen("shuffle.in","r",stdin);
    freopen("shuffle.out","w",stdout);
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> A[i];
        P[A[i]] = i;
    }
    for(int i = 1;i <= N;i++){
        int id;
        cin >> id;
        V[P[P[P[i]]]] = id;
    }
    for(int i = 1;i <= N;i++){
        cout << V[i] << "\n";
    }
    return 0;
}
