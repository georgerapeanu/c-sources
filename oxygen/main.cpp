#include <iostream>

using namespace std;
int N,M,L,K;
int i,j,l,k;
a,b,c,d
int A[37][37][37][37];
int main()
{
    cin>>N>>M>>L>>K>>a>>b>>c>>d;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            for(l=1;l<=L;l++)
            {
                for(k=1;k<=K;k++)
                {
                    cin>>A[i][j][l][k];
                    A[i][j][l][k]=A[i-1][j][l][k]+A[i][j-1][l][k]+A[i][j][l-1][k]+A[i][j][l][k-1]-A[i-1][j-1][l][k]-A[i-1][j][l-1][k]-A[i-1][j][l][k-1]-A[i][j-1][l-1][k]-A[i][j-1][l][k-1]-A[i][j][l-1][k-1]+A[i-1][j-1][l-1][k]+A[i-1][j-1][l][k-1]+A[i-1][j][l-1][k-1]+A[i][j-1][l-1][k-1]-A[i-1][j-1][l-1][k-1]+A[i][j][k][l];
                }
            }
        }
    }
    for(i=1; i<=N-a+1; i++)
         for(j=1; j<=M-b+1; j++)
             for( k=1; k<=K-c+1; k++)
                for(l=1; l<=L-l+1; l++)
                    {

                    }
    return 0;
}
