#include <iostream>
#include <iomanip>
using namespace std;
int N,M;
int main()
{
    cin>>N>>M;
    cout<<(M*1900+(N-M)*100)*(1<<M);
    return 0;
}
