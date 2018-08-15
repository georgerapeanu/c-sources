#include <iostream>
using namespace std;
int val;
int nr;
int main()
{
    cin>>val;
    while(val)
    {
        nr+=(val%8==1);
        val/=8;
    }
    cout<<nr;
    return 0;
}
