#include <vector>
#include <iostream>
using namespace std;
int N;
vector<int> G[1005];
string A[1005],B[1005];
bool ok;
string rez[1005];
set<string> elem;
bool dfs(int nod)
{

}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i]>>B[i];
    }
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            if(A[i].substr(0,3)==A[j].substr(0,3))
                G[i].push_back(j),G[j].push_back(i);

    return 0;
}
