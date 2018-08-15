#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int x3;
int x2;
int y3;
int y2;
int main()
{
    cin>>x3>>y3>>x2>>y2;
    cout<<max(abs(x3-x2),abs(y3-y2));
    return 0;
}
