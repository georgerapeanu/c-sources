#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
using namespace std;
vector<int> G[26];
int gr[26];
string a,b;
int N;
queue<int> Q;
bitset<26> U;
string rez;
int main()
{
    cin>>N;
    cin>>a;
    for(int i=2;i<=N;i++)
    {
        cin>>b;
        int poz=0;
        while(poz<a.size()&&poz<b.size()&&a[poz]==b[poz])
            poz++;
        if(poz==a.size()||poz==b.size()){if(a.size()>b.size()){cout<<"Impossible";return 0;}}
        else
        {
            G[a[poz]-'a'].push_back(b[poz]-'a');
            gr[b[poz]-'a']++;
        }
        a=b;
    }
    for(int i=0;i<26;i++)
        if(!gr[i])
            Q.push(i);
    while(!Q.empty())
    {
        rez+=Q.front()+'a';
        U[Q.front()]=1;
        for(auto it:G[Q.front()])
        {
            gr[it]--;
            if(gr[it]==0)
                Q.push(it);
        }
        Q.pop();
    }
    for(int i=0;i<26;i++)
    if(!U[i]){cout<<"Impossible";return 0;}
    cout<<rez;
    return 0;
}
