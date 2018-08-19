#include <iostream>
#include <map>
using namespace std;
map<long long,long long> M;
int N;
long long V[100005];
long long S,s;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        S+=V[i];
    }
    if(S%2==1){cout<<"NO";return 0;}
    for(int i=N;i>=0;i--)
    {
        if(S-s>S/2);
        else if(s==S/2&&i<N){cout<<"YES";return 0;}
        else
        {
            if(M[S/2-(S-s)]&&i<N-1){cout<<"YES";return 0;}
        }
        s+=V[i];
        M[V[i]]=1;
    }
    M.clear();
    s=0;
    for(int i=1;i<=N;i++)
    {
        if(S-s>S/2);
        else if(s==S/2&&i>1){cout<<"YES";return 0;}
        else
        {
            if(M[S/2-(S-s)]&&i>2){cout<<"YES";return 0;}
        }
        s+=V[i];
        M[V[i]]=1;
    }
    cout<<"NO";
    return 0;
}
