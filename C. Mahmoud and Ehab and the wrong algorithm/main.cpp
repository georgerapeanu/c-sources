#include <iostream>
#include <cassert>

using namespace std;
int N;
int main(){
    cin >> N;
    if(N >= 6){
       for(int i = 2;i < N - 1;i++){
            cout << "1 " << i << "\n";
       }
       cout << "2 " << N - 1 << "\n";
       cout << "2 " << N << "\n";
    }
    else{
        cout << "-1\n";
    }
    for(int i = 1;i < N;i++){
        cout << i << " " << i + 1 << "\n";
    }
    return 0;
}
