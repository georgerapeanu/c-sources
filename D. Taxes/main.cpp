#include <iostream>

using namespace std;
unsigned long long N;
bool prim=1;
int main()
{
    cin>>N;
    for(unsigned long long i=2;i*i<=N;i++)
        if(N%i==0)
        {
            prim=0;
            break;
        }
    if(prim)
        cout<<1;
    else
    {
        if(N%2==0)
            cout<<2;
        else
        {
            prim=1;
            for(unsigned long long i=2;i*i<=N-2;i++)
                if((N-2)%i==0)
                {
                    prim=0;
                    break;
                }
            if(prim)
                cout<<2;
            else
                cout<<3;
        }
    }
    return 0;
}
