#include <iostream>

using namespace std;
int N;
long long A[305][305];
bool take[305][305];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)cin>>A[i][j];
    for(int k=1;k<=N;k++)
    {
        for(int i=1;i<=N;i++)
        {
            if(i!=k&&A[i][k])
            {
                for(int j=1;j<=N;j++)
                {
                    if(j!=k&&j!=i&&A[j][k])
                    {
                        if(!A[i][j]||A[i][j]>A[i][k]+A[j][k])
                        {
                            cout<<-1;
                            return 0;
                        }
                    }
                }
            }
        }
    }
    long long rez=0;
    for(int k=1;k<=N;k++)
    {
        for(int i=1;i<=N;i++)
        {
            if(i!=k&&A[i][k])
            {
                for(int j=1;j<=N;j++)
                {
                    if(j!=k&&j!=i&&A[j][k])
                    {
                        if(A[i][j]==A[i][k]+A[j][k])
                        {
                            take[i][j]=1;
                        }
                    }
                }
            }
        }
    }
    for(int i=1;i<=N;i++)for(int j=1;j<i;j++)rez+=(A[i][j]*(!take[i][j]));
    cout<<rez;
    return 0;
}
