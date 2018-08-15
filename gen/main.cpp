
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;
int N,M,C;
int main()
{
    srand(time(NULL));
    freopen("in","w",stdout);
    int N = rand() % 20 + 1;
    int M = rand() % 20 + 1;
    cout << N << " " << M << "\n";
    for(int i = 1;i <= N;i++){
        int a = rand() % 200 + 1;
        int b = rand() % 200 + 1;
        cout << min(a,b) << " " << max(a,b) << "\n";
    }
    for(int i = 1;i <= N;i++){
        int a = rand() % N + 1;
        int b = rand() % N + 1;
        cout << min(a,b) << " " << max(a,b) << "\n";
    }

    return 0;
}
