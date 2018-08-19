#include <iostream>
#define B 22
using namespace std;
int F[1<<B];
int N;
int A[1<<B];
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int T=1;
    while(T--)
    {
        cin>>N;
        for(int i=0;i<(1<<B);i++)F[i]=-1;
        for(int i=1;i<=N;i++)
        {cin>>A[i];F[A[i]]=A[i];}
        for(int j=0;j<B;j++)
            for(int i=(1<<B)-1;i;i--)
                if((i&(1<<j))&&F[i^(1<<j)]!=-1)
                    F[i]=F[i^(1<<j)];
        for(int i=1;i<=N;i++)
        {
            cout<<F[(1<<B)-1-A[i]]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
