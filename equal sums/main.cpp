#include <iostream>

using namespace std;
int N;
int A[1005][1005];
int maxs,L[1005],C[1005],rez;
int main() {
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            cin>>A[i][j];
            L[i]+=A[i][j];
            C[j]+=A[i][j];
        }
    }
    for(int i=1;i<=N;i++)
    {
        maxs=max(maxs,max(L[i],C[i]));
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            int m=min(maxs-L[i],maxs-C[j]);
            A[i][j]+=m;
            L[i]+=m;
            C[j]+=m;
            cout<<A[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
