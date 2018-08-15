#include <iostream>
using namespace std;
int N;
long long V[400005];
int poz[400005],i,j;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(i=1;i<=N;i++)
    {
        cin>>V[i];
        V[i]=(V[i-1]+V[i])%N;
        if(poz[V[i]]||!V[i])
            break;
        poz[V[i]]=i;
    }
    cout<<i-poz[V[i]]<<"\n";
    for(j=poz[V[i]]+1;j<=i;j++)
        cout<<j<<" ";
    return 0;
}
