#include <iostream>
#include <algorithm>
using namespace std;
int N,K,x,cnt[105];
int have[5];
int main()
{
    cin>>N>>K;have[4]=N;have[2]=2*N;
    for(int i=1;i<=K;i++)
    {
        cin>>x;
        while(x>=3)
            if(have[4])have[4]--,x-=4;
            else if(have[2])have[2]--,x-=2;
            else {cout<<"NO";return 0;}
        if(x>0)cnt[x]++;
    }
    while(cnt[2])
        if(have[2])have[2]--,cnt[2]--;
        else if(have[4])have[4]--,cnt[2]--,have[1]++;
        else cnt[1]+=2,cnt[2]--;
    cout<<(cnt[1]<=have[1]+have[2]+2*have[4] ? "YES":"NO");
    return 0;
}
