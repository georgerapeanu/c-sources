#include <iostream>
using namespace std;
int V[100005];
int N;
int solve(int st,int dr)
{
    if(st>dr)return 0;
    if(st==dr)return V[st]==st;
    int op=0;
    if(V[st]==st)
    {
        swap(V[st],V[st+1]);op++;
    }
    if(V[dr]==dr)
    {
        swap(V[dr],V[dr-1]);op++;
    }
    return op+solve(st+1,dr-1);
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
    }
    cout<<solve(1,N);
    return 0;
}
