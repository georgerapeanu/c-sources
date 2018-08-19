#include <iostream>
#include <cstdio>
using namespace std;
//int dp[100][100];
int T,x,y;
int main()
{
    //freopen("out","w",stdout);
    cin>>T;
    while(T--)
    {
        cin>>x>>y;
        if(x<y)swap(x,y);
        if(x%2==1)cout<<"hasan";
        else cout<<(x%2!=y%2 ? "hasan":"abdullah");
        cout<<"\n";
    }
    return 0;
}
