#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int A,B,RA,RB;
vector<int> G[1000005];
queue<int> Q;
int ind=0;
int nod=1;
string a;
int dist[1000005];
void dfs(int N)
{
    if(ind==A)RA=N;
    if(ind==B)RB=N;
    while(ind<a.size()&&a[ind]=='U')
    {
        ind++;
        nod++;
        G[N].push_back(nod);
        G[nod].push_back(N);
        dfs(nod);
        if(ind==A)RA=N;
        if(ind==B)RB=N;
    }
    ind++;
}
int main()
{
    cin>>A>>B>>a;
    dfs(1);
    A=RA;B=RB;
    Q.push(A);
    dist[A]=1;
    while(!Q.empty())
    {
        int nod=Q.front();Q.pop();
        for(auto it:G[nod])
            if(!dist[it]){dist[it]=dist[nod]+1;Q.push(it);}
    }
    cout<<dist[B]-1;
    return 0;
}
