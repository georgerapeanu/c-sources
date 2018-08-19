#include <iostream>
using namespace std;
long long D[10][90],rez,S;
int N;
int main()
{
    cin>>S;
    D[0][0]=1;
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=S;j++)
        {
            for(int k=0;k<=9&&k<=j;k++)
                D[i][j]+=D[i-1][j-k];
        }
    }
    D[1][0]=1;
    for(int i=1;i<=9;i++)
    {
        rez+=D[i][S];
    }
    if(S==1)
        rez++;
    cout<<rez;
    return 0;
}
