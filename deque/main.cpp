#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

ifstream f("deque.in");
ofstream g("deque.out");

int n,k,X[5000001],i;
long long S;
deque <int> dq;
int main()
{
    f>>n>>k;
    f>>X[1];
    dq.push_front(1);
    for(i=2;i<=n;i++)
    {
        f>>X[i];
        while(!dq.empty() && X[dq.back()]>=X[i])
            dq.pop_back();
        dq.push_back(i);
        if(i>=k)
        {
            //cout<<dq.front()<<'\n';
            if(i-k>=dq.front())
            {
                dq.pop_front();
                //cout<<dq.front()<<'\n';
            }
            S=S+X[dq.front()];
        }
    }
    //for(i=1;i<=n;i++)
        //cout<<X[i]<<" ";
    g<<S;
    f.close();
    g.close();
    return 0;
}
