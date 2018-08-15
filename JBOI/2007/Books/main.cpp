#include <iostream>
using namespace std;
int N;
bool ok[55][55];
int V[55][55];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            cin>>V[i][j];
    int ma=0;
    for(int i=1;i<=N;i++)
    {
        ma=0;for(int j=1;j<=N;j++){ok[i][j]|=(ma<V[i][j]);ma=max(ma,V[i][j]);}
        ma=0;for(int j=N;j;j--){ok[i][j]|=(ma<V[i][j]);ma=max(ma,V[i][j]);}
        ma=0;for(int j=1;j<=N;j++){ok[j][i]|=(ma<V[j][i]);ma=max(ma,V[j][i]);}
        ma=0;for(int j=N;j;j--){ok[j][i]|=(ma<V[j][i]);ma=max(ma,V[j][i]);}
    }
    int nr=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            nr+=ok[i][j];
    cout<<nr;
    return 0;
}
