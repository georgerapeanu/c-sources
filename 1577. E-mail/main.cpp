#include <iostream>
#include <cstring>
#define MOD 1000000007
using namespace std;
long long nrmod[2005][2005];
int mindim[2005][2005],N,M;
char A[2005],B[2005];
int main()
{
    cin.getline(A+1,2005);N=strlen(A+1);
    cin.getline(B+1,2005);M=strlen(B+1);
    for(int i=0;i<=N;i++)
    {
        nrmod[i][0]=1;
        mindim[i][0]=i;
    }
    for(int i=0;i<=M;i++)
    {
        nrmod[0][i]=1;
        mindim[0][i]=i;
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
           if(A[i]==B[j])
           {
               nrmod[i][j]=nrmod[i-1][j-1];
               mindim[i][j]=mindim[i-1][j-1]+1;
           }
           else
           {
               mindim[i][j]=min(mindim[i-1][j],mindim[i][j-1])+1;
               nrmod[i][j]=((mindim[i-1][j]==mindim[i][j]-1)*(nrmod[i-1][j])+(mindim[i][j-1]==mindim[i][j]-1)*(nrmod[i][j-1]))%MOD;
           }
        }
    }
    cout<<nrmod[N][M];
    return 0;
}
