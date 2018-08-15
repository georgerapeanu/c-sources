#include <iostream>
using namespace std;
bool V[1005][1005][4];
bool D[1005][1005];
int N,M,rez;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            cin>>D[i][j];
            V[i][j][0]=V[i-1][j][0]|D[i][j];
            V[i][j][3]=V[i][j-1][3]|D[i][j];
        }
    }
    for(int i=N;i;i--)
    {
        for(int j=M;j;j--)
        {
            V[i][j][1]=V[i][j+1][1]|D[i][j];
            V[i][j][2]=V[i+1][j][2]|D[i][j];
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
            rez=rez+(V[i][j][0]+V[i][j][1]+V[i][j][2]+V[i][j][3])*(!D[i][j]);
    }
    cout<<rez;
    return 0;
}
