#include <iostream>
#include <algorithm>
using namespace std;
int N,A,B;
int main()
{
    cin >> N >> A >> B;
    if(abs(A - B) % 2 == 0){
        cout << "Alice";
    }
    else {
        cout << "Borys";
    }
    return 0;
}
