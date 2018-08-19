#include <iostream>
using namespace std;
int N;
int V[1005];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        if(V[i]%V[1]!=0){cout<<-1;return 0;}
    }
    cout<<2*N-1<<"\n";
    cout<<V[1]<<" ";
    for(int i=2;i<=N;i++)///....
        cout<<V[i]<<" "<<V[1]<<" ";
    return 0;
}
