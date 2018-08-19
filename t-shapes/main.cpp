#include <iostream>

using namespace std;
int N,M,nr;
char C[205][205];
int main()
{
    cin>>N>>M;
    cin.getline(C[0],205);
    for(int i=1;i<=N;i++)
    {
        cin.getline(C[i]+1,205);
    }
    for(int i=1;i<=N-2;i++)
    {
        for(int j=1;j<=M-2;j++)
        {
            if(C[i][j]=='t'&&C[i][j+1]=='t'&&C[i][j+2]=='t'&&C[i+1][j+1]=='t'&&C[i+2][j+1]=='t')
                nr++;
        }
    }
    cout<<nr;
    return 0;
}
