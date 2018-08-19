#include <iostream>

using namespace std;
long long N,Q;
int main()
{
    cin>>Q;
    while(Q)
    {
        cin>>N;
        bool ok=0;
        for(int i=0;i<7&&N>=4*i&&!ok;i++)
        {
            if((N-4*i)%7==0)
                {ok=1;}
        }
        if(ok)
            cout<<"Yes\n";
        else
            cout<<"No\n";
        Q--;
    }
    return 0;
}
