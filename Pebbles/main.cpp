#include <iostream>
using namespace std;
int N;
int V[1005];
int T;
int main()
{
    cin>>T;
    while(T--)
    {
        int xo=0;
        cin>>N;
        for(int i=1;i<=N;i++)cin>>V[i];
        for(int i=N;i;i--)V[i]=V[i]-V[i-1];
        for(int i=1;i<=N;i++)
        {
            if((N-i)%2==0)
            {
                xo^=V[i];
            }
        }
        cout<<(xo==0 ? "NIE\n":"TAK\n");
    }
    return 0;
}
