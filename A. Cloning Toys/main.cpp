#include <iostream>

using namespace std;
int x,y;
int main()
{
    cin >> x >> y;
    if(y == 0){
        cout << "No";
        return 0;
    }
    if(y == 1 && x != 0){
        cout << "No";
        return 0;
    }
    y--;
    if(x < y){
        cout << "No";
        return 0;
    }
    x -= y;
    if(x % 2 == 1){
        cout << "No";
        return 0;
    }
    cout << "Yes";
    return 0;
}
