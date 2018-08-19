#include <iostream>
#include <bitset>
using namespace std;
int N;
int nr;
int val,rez;
bitset<100005> B;
int main()
{
    cin>>N;
    for(int i=1;i<=2*N;i++)
    {
        cin>>val;
        if(B[val])
            nr--;
        else
            B[val]=1,nr++;
        rez=max(nr,rez);
    }
    cout<<rez;
    return 0;
}
