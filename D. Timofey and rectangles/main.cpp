#include <iostream>

using namespace std;
int N,X,XX,Y,YY;
pair<int,int> V[500005];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>X>>Y>>XX>>YY;
        V[i]=make_pair(X,Y);
    }
    cout<<"YES\n";
    for(int i=1;i<=N;i++)
    {
        X=V[i].first;Y=V[i].second;
        cout<<1+(((X%2+2)%2)<<1)+(Y%2+2)%2<<"\n";
    }
    return 0;
}
