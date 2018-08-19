#include <iostream>
#include <algorithm>
using namespace std;
int N;
int V[105];
int rez=1<<30;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
    }
    sort(V+1,V+1+N);
    for(int i=V[1];i<=V[N];i++)
    {
        rez=min(rez,min(i-V[1]+V[N]-V[1],V[N]-V[1]+V[N]-i));
    }
    cout<<rez;
    return 0;
}
