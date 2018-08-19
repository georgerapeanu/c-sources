#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f=fopen("dominouri.in","r");
FILE *g=fopen("dominouri.out","w");
int N;
int K[100005];
int cost[100005],len,val;
int A[100005];
vector<int> V[100005];
void dfs(int nod)
{
    vector<int> tmp;
    for(auto it:V[nod])
    {
        dfs(it);
        tmp.push_back(cost[it]);
    }
    nth_element(tmp.begin(),tmp.begin()+A[nod],tmp.end());
    for(int i=0;i<A[nod];i++)
        cost[nod]+=tmp[i];
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&len);
        if(!len)
            cost[i]=1;
        for(int j=1;j<=len;j++)
        {
            fscanf(f,"%d",&val);
            V[i].push_back(val);
        }
    }
    for(int i=1;i<=N;i++) {fscanf(f,"%d",&A[i]);}
    dfs(1);
    fprintf(g,"%d",cost[1]);
    return 0;
}
