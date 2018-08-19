#include <iostream>
#include <algorithm>
#include <bitset>
using namespace std;
bitset<(1<<19)+1> is;
int B[(1<<19)+1];
int N;
int val;
int nr,valmax;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;nr=N;
    for(int i=1;i<=N;i++) {cin>>val;is[val]=1;}
    for(int i=1;i<=(1<<19);i++)
    {
        for(int j=0;j<=19;j++)
            if(i&(1<<j))
                B[i]|=B[i-(1<<j)];
        if(is[i]&&B[i]==i)
            nr--;
        if(is[i])
            B[i]=i;
    }
    cout<<nr;
    return 0;
}
