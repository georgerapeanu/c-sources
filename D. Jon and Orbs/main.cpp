#include <iostream>
#define EPS (5e-12)
#define POZ (j%2)
using namespace std;
int K;
const int ZMAX=10005;
double P[ZMAX+1][1005];
int N;
int Q;
int main()
{
    cin>>K>>Q;
    P[0][0]=1;
    for(int i=1;i<=ZMAX;i++)
    {
        for(int j=1;j<=K;j++)
        {
            P[i][j]=((K-j+1)*P[i-1][j-1]+j*P[i-1][j])/K;
        }
    }

    for(int i=1;i<=Q;i++)
    {
        double p;
        cin>>p;
        p=(p-EPS)/2000;
        for(int j=1;j<=ZMAX;j++)
            if(P[j][K]>=p)
            {
                cout<<j<<"\n";break;
            }
    }
    return 0;
}

