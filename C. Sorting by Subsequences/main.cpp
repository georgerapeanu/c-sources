#include <iostream>
#include <vector>
#include <map>
using namespace std;
map<int,int> M;
int N;
int V[100005];
bool viz[100005];
vector<int> ciclu[100005];
int nr=0;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        M[V[i]]=1;
    }
    int ind=1;
    for(auto &it:M)
    {
        it.second=ind++;
    }
    for(int i=1;i<=N;i++)
    {
        if(!viz[i])
        {
            nr++;
            int nod=i;
            while(!viz[nod])
            {
                viz[nod]=1;
                ciclu[nr].push_back(nod);
                nod=M[V[nod]];
            }
        }
    }
    cout<<nr<<"\n";
    for(int i=1;i<=nr;i++)
    {
        cout<<ciclu[i].size()<<" ";
        for(auto it:ciclu[i])cout<<it<<" ";
        cout<<"\n";
    }
    return 0;
}
