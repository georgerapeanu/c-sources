#include <bitset>
#include <iostream>
#include<algorithm>
using namespace std;
int d[1006];
pair<int,int> P[1006];
bitset<1006> S;
int N,T,M;
int main() {
    cin>>N>>T;
    for(int i=1;i<=N;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        P[i]=make_pair(b,c);
        S[i]=a;

    }
    for(int i=1;i<=N;i++)
    {
        d[i]=(1<<30);
        for(int j=1;j<=N;j++)
            if(S[j])
                d[i]=min(d[i],abs(P[i].first-P[j].first)+abs(P[i].second-P[j].second));
    }
    cin>>M;
    for(int i=1;i<=M;i++)
    {
        int A,B;
        cin>>A>>B;
        cout<<min(d[A]+d[B]+T,abs(P[A].first-P[B].first)+abs(P[A].second-P[B].second))<<"\n";
    }
    return 0;
}
