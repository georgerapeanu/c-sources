#include <iostream>
#include <algorithm>
using namespace std;
string a,reva;
int main()
{
    cin >> a;
    reva = a;
    reverse(reva.begin(),reva.end());
    cout << a + reva;
    return 0;
}
