#include <iostream>

using namespace std;
int N,rez;
int main()
{
    cin >> N;
    for(int i = 1;i <= N;i++){
        if((N - i) % i == 0){
            rez++;
        }
    }
    cout << rez - 1;
    return 0;
}
