#include <iostream>
#include <stack>
using namespace std;
int N;
int A[200005];
stack<int> S,D;
stack<int> SB,DB;
int st[200005];
int dr[200005];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        dr[i]=N+1;
    }
    for(int i=1;i<=N;i++)
    {
        while(!S.empty()&&A[S.top()]<A[i])S.pop();
        while(!SB.empty()&&(A[SB.top()]|A[i])==A[i])SB.pop();
        st[i]=max((S.size() ? S.top():0),(SB.size() ? SB.top():0));
        S.push(i);
        SB.push(i);
    }
    for(int i=N;i;i--)
    {
        while(!D.empty()&&A[D.top()]<=A[i])D.pop();
        while(!DB.empty()&&(A[DB.top()]|A[i])==A[i])DB.pop();
        dr[i]=min((D.size() ? D.top():N+1),(DB.size() ? DB.top():N+1));
        D.push(i);
        DB.push(i);
    }
    long long rez=1LL*N*(N+1)/2;
    for(int i=1;i<=N;i++)
    {
        rez-=1LL*(dr[i]-i)*(i-st[i]);
    }
    cout<<rez;
    return 0;
}
