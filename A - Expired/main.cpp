#include <iostream>

using namespace std;
long long X,A,B;
int main()
{
    cin>>X>>A>>B;
    if(-A+B<=0){cout<<"delicious";}
    else if(-A+B<=X){cout<<"safe";}
    else cout<<"dangerous";
    return 0;
}
