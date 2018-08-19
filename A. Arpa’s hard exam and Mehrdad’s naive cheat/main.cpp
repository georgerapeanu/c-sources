#include <iostream>

using namespace std;
int N;
int p(int N)
{
    int r=1;
    int c=8;
    while(N)
    {
        if(N%2)
        {
            r=(r*c)%10;
        }
        c=(c*c)%10;
        N/=2;
    }
    return r;
}
int main()
{
    cin>>N;
    cout<<p(N);
    return 0;
}
