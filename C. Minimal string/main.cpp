#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;
char C[100005];
string S,rez;
stack <int> a,b;
int main()
{
    cin>>S;
    for(int i=0;i<S.size();i++)
        C[i]=S[i];
    for(int i=S.size()-1;i>=0;i--)
        a.push(i);
    for(int i=S.size()-2;i>=0;i--)
        C[i]=min(C[i+1],S[i]);
    while(!a.empty())
    {
        if(b.empty()||C[a.top()]<S[b.top()])
        {
            while(C[a.top()]!=S[a.top()])
            {
                b.push(a.top());
                a.pop();
            }
            rez+=S[a.top()];
            a.pop();
        }
        else
        {
            rez+=S[b.top()];
            b.pop();
        }
    }
    while(!b.empty())
    {
        rez+=S[b.top()];
        b.pop();
    }
    cout<<rez;
    return 0;
}
