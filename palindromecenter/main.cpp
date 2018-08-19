#include <iostream>
using namespace std;
int V[100005];
int R[200005];
int N,id=0;
int main() {
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        if(V[i]%2)
        {
            R[2*(i-V[i]/2)]=max(V[i],R[2*(i-V[i]/2)]);
        }
        else
        {
            R[2*(i-V[i]/2)+1]=max(V[i]+1,R[2*(i-V[i]/2)+1]);
        }
    }
    bool ok=1;
    while(ok)
    {
        ok=0;id=0;
        for(int i=1;i<=2*N;i++)
        {
            if(id+R[id]>=i)
            {
                if(R[i]<min(R[2*id-i],id+R[id]-i))
                {
                    ok=1;
                    R[i]=min(R[2*id-i],id+R[id]-i);
                }
                else if(R[2*id-i]<min(R[i],id+R[id]-i))
                {
                    ok=1;
                    R[2*id-1]=min(R[i],id+R[id]-i);
                }
            }
            if(id+R[id]<i+R[i])
                id=i;
        }
    }
    for(int i=2;i<=2*N;i+=2)
        cout<<R[i]<<" ";
    return 0;
}
