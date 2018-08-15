#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> G[100005];
int nr,N;
int dfs(int nod,int tata)
{
    vector<int> nr;nr.clear();
    for(auto it:G[nod])
        if(it!=tata)
            nr.push_back(dfs(it,nod));
    sort(nr.begin(),nr.end());
    int rez=0;
    for(int i=0;i<nr.size();i++)
    {
        rez=max(rez,nr[i]+(int)nr.size()-i);
    }
    return rez;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        while(1)
        {
            cin>>nr;
            if(!nr)
                break;
            G[i].push_back(nr);
            G[nr].push_back(i);
        }
    }
    cin>>nr;
    cout<<dfs(nr,0);
    return 0;
}
