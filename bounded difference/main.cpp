#include <iostream>
#include <algorithm>
using namespace std;
int N;
long long K;
long long A[100006];
int ind=0;
int V[200006];
int nr;
bool eval()
{
    for(int i=1;i<=V[0];i++)
    {
        if((V[i]!=1&&abs(A[V[i]]-A[V[i]-1])>K)||(V[i]!=N&&abs(A[V[i]]-A[V[i]+1])>K))
            return 0;
    }
    return 1;
}
int main() {
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        if(i!=N&&abs(A[i]-A[i+1])>K)
        {
            if(!ind)ind=i;
            V[++V[0]]=i;
        }
    }
    if(!ind){cout<<0;return 0;}
    for(int i=1;i<=N;i++)
    {
        swap(A[i],A[ind]);
        if(eval())
        {
            cout<<i<<" "<<ind;return 0;
        }
        swap(A[i],A[ind]);
    }
    ind++;
    for(int i=1;i<=N;i++)
    {
        swap(A[i],A[ind]);
        if(eval())
        {
            cout<<i<<" "<<ind;return 0;
        }
        swap(A[i],A[ind]);
    }
    cout<<-1;
    return 0;
}
