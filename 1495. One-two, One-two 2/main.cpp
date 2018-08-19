#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
struct {int prev,cf;} P[1000005];
bool viz[1000005];
int N;
queue <int> Q;
int rez[35];
int main()
{
    cin>>N;
    if(N<3)
    {
        cout<<N;
        return 0;
    }
    Q.push(1);
    Q.push(2);
    P[1].cf=0;
    P[2].cf=1;
    viz[1]=viz[2]=1;
    while(!viz[0]&&!Q.empty())
    {
        int r=Q.front();
        Q.pop();
        if(!viz[(r*10+1)%N])
        {
            Q.push((r*10+1)%N);
            P[(r*10+1)%N].cf=0;
            P[(r*10+1)%N].prev=r;
            viz[(r*10+1)%N]=1;
        }
        if(!viz[(r*10+2)%N])
        {
            Q.push((r*10+2)%N);
            P[(r*10+2)%N].cf=1;
            P[(r*10+2)%N].prev=r;
            viz[(r*10+2)%N]=1;
        }
    }
    if(!viz[0])
        cout<<"Impossible";
    else
    {
        int r=0;
        do
        {
            rez[++rez[0]]=P[r].cf;
            r=P[r].prev;
            if(rez[0]>30)
                break;
        }
        while(r);
        if(rez[0]>30)
            cout<<"Impossible";
        else
        {
            for(int i=rez[0];i;i--)
                cout<<rez[i]+1;
        }
    }
    return 0;
}
