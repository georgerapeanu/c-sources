#include <iostream>
using namespace std;
int N;
int V[305];
int ind=1;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>V[i];
    while(ind<=N)
    {
        if(!V[ind])
        {
            if(ind!=N)cout<<"R";
            ind++;
            continue;
        }
        cout<<"P";V[ind]--;
        if(ind!=N)cout<<"RL";
        else cout<<"LR";
    }
    return 0;
}
