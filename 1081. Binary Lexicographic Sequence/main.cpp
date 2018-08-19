#include <iostream>
using namespace std;
int N,K;
int fib[47];
bool rez[47];
int main()
{
    fib[1]=1;
    fib[2]=1;
    cin>>N>>K;
    for(int i=2;i<=N+2;i++)
        fib[i]=fib[i-1]+fib[i-2];
    for(int i=1;i<=N;i++)
    {
        if(K>fib[N-i+2])
        {
            rez[i]=1;
            K-=fib[N-i+2];
            i++;
        }
        else
        {
            ;
        }
    }
    if(K>1)
        cout<<-1;
    else
        for(int i=1;i<=N;i++)
            cout<<rez[i];
    return 0;
}
