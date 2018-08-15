#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <bitset>
#define NRMAX 30000
using namespace std;
int N;
map<string,int> M;
map<int,string> rev;
string a,b,t;
vector<int> G[NRMAX];
int nr;
vector<int> tmp;
int gr[NRMAX];
bitset<NRMAX> viz;
void dfs(int nod,int spaces)
{
    if(viz[nod])return ;
    viz[nod]=1;
    for(int j=1;j<=spaces;j++)
        cout<<" ";
    t=rev[nod];
    int ind=t.size()-1;
    while(ind>=0&&t[ind]!='\\')
        ind--;
    ind++;
    cout<<t.substr(ind)<<"\n";
    for(auto it:G[nod])
    {
        dfs(it,spaces+1);
    }
}
bool cmp(int a,int b)
{
    return rev[a]<rev[b];
}
vector<int> tosolve;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;a+='\\';
        b.clear();
        tmp.clear();
        for(auto it:a)
        {
            if(it=='\\')
            {
                if(!M[b]){M[b]=++nr;rev[nr]=b;}
                tmp.push_back(M[b]);
            }
            b+=it;
        }
        for(int i=0;i<tmp.size()-1;i++)
            {G[tmp[i]].push_back(tmp[i+1]);gr[tmp[i+1]]++;}
    }
    for(int i=1;i<=nr;i++)
    {
        sort(G[i].begin(),G[i].end(),cmp);
        if(!gr[i])
        {
            tosolve.push_back(i);
        }
    }
    sort(tosolve.begin(),tosolve.end(),cmp);
    for(auto it:tosolve)
        dfs(it,0);
    return 0;
}
