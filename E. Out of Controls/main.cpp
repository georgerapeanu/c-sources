#include <iostream>
using namespace std;
int A[11][11];
int N,r;
#def\
ine fo fo\
r
int main()
{
    cin>>N;
    fo(int i=1;i<=N;i++)
        fo(int j=1;j<=N;j++)
            cin>>A[i][j];
    fo(int k=1;k<=N;k++)
        fo(int i=1;i<=N;i++)
            fo(int j=1;j<=N;j++)
                {A[i][j]=min(A[i][k]+A[k][j],A[i][j]);}
    fo(int i=1;i<=N;i++)
        fo(int j=1;j<=N;j++)
            r=max(r,A[i][j]);
    cout<<r;
    return 0;
}
