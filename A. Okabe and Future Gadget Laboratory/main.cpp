#include <iostream>
using namespace std;
int N;
int A[55][55];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            cin>>A[i][j];
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(A[i][j]!=1)
            {
                bool ok=0;
                for(int s=1;s<=N&&!ok;s++)
                {
                    for(int t=1;t<=N&&!ok;t++)
                    {
                        if(A[i][j]==A[i][s]+A[t][j])ok=1;
                    }
                }
                if(!ok){cout<<"No";return 0;}
            }
        }
    }
    cout<<"Yes";
    return 0;
}
