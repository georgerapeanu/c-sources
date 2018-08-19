#include <iostream>
using namespace std;
bool f[6000];
int val,i,N,rez;
int main()
{
    cin>>N;
    for(i=1;i<=N;i++)
    {
        cin>>val;
        if(!f[val]&&val<=N)
            f[val]=1;
        else
            rez++;
    }
    cout<<rez;
    return 0;
}
