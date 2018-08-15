#include <iostream>
#include <bitset>
#include <algorithm>
using namespace std;
long long N,i,a,b,c;
int main()
{
    cin>>N;
    for(a=N/1234567;a>=0;a--)
        for(b=(N-a*1234567)/123456;b>=0&&a%2==N%2;b--)
            {
                if((N-a*1234567-b*123456)%1234==0)
                {
                    cout<<"YES";
                    return 0;
                }
            }
    cout<<"NO";
    return 0;
}
