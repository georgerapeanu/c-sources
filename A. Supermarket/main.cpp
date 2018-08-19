#include <iostream>
#include <iomanip>
using namespace std;
double bst = 1e9;
int N,M;
int a,b;
int main()
{
    cin >> N >> M;
    while(N--){
        cin >> a >> b;
        bst = min(bst,(double)a / b);
    }
    cout << fixed << setprecision(8) << bst * M;
    return 0;
}
