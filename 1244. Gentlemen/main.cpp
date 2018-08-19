#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
pair<int,int> V[105];
int P[100005];
vector <int> rez[100005];
int tmp[100005];
int N,S,val;
int main()
{
    cin>>val>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first;
        S+=V[i].first;
        V[i].second=i;
    }
    sort(V+1,V+1+N);
    P[0]=1;
    for(int i=1;i<=N;i++)
    {
        for(int j=S-V[i].first;j>=0;j--)
        {
            if(P[j]&&P[j+V[i].first]<2)
            {
                P[j+V[i].first]+=P[j];
                if(P[j+V[i].first]>=2)
                {
                    P[j+V[i].first]=2;
                    rez[j+V[i].first].clear();
                }
                else
                {
                    rez[j+V[i].first].assign(rez[j].begin(),rez[j].end());
                    rez[j+V[i].first].push_back(V[i].second);
                }
            }
        }
    }
    if(P[val]==0)
        cout<<0;
    else if(P[val]==2)
        cout<<-1;
    else
    {
        sort(rez[val].begin(),rez[val].end());
        int ind=0;
        for(int i=1;i<=N;i++)
        {
            if(i==rez[val][ind])
            {
                ind++;
            }
            else
                cout<<i<<" ";
        }
    }
    return 0;
}
