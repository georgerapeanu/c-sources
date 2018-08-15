#include <iostream>
#define val first
#define tip second
using namespace std;
int Ev[200005];
int S[200005];
int l,r;
int N,K,Q;
int main()
{
    cin>>N>>K>>Q;
    for(int i=1;i<=N;i++)
    {
        cin>>l>>r;
        Ev[l]++;
        Ev[r+1]--;
    }
    int ev=0;
    for(int i=1;i<=200005;i++)
    {
        ev+=Ev[i];
        S[i]=S[i-1]+(ev>=K);
    }
    for(int i=1;i<=Q;i++)
    {
        cin>>l>>r;
        cout<<S[r]-S[l-1]<<"\n";
    }
    return 0;
}
