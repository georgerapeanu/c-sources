#include <iostream>
#define B 20
using namespace std;
int F[1<<B];
int N;
int A[1<<B];
int main()
{
    int T;cin>>T;
    while(T--)
    {
        cin>>N;
        for(int i=0;i<(1<<B);i++)F[i]=0;
        for(int i=1;i<=N;i++)
        {cin>>A[i];F[A[i]]++;}
        for(int j=0;j<B;j++)
            for(int i=(1<<B)-1;i;i--)
                if((i&(1<<j)))
                    F[i]+=F[i^(1<<j)];
        int rez=0;
        for(int i=1;i<=N;i++)
        {
            rez+=F[(1<<B)-1-A[i]];
        }
        cout<<rez<<"\n";
    }
    return 0;
}
