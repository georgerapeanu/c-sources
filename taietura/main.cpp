#include <cstdio>
#include <map>
#include <vector>
using namespace std;
FILE *f=fopen("taietura.in","r");
FILE *g=fopen("taietura.out","w");
map<long long,vector<int> > M;///gj testul 9 "orice element din sirul V este mai mic sau egal in valoare absoluta cu 109"
long long int s;
int val;
int N;
int V[100005];
int main()
{
    fscanf(f,"%d",&N);
    M[0].push_back(0);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        s+=val;
        M[s].push_back(i);
    }
    for(auto it:M)
    {
        for(int i=0;i<it.second.size();i++)
        {
            V[it.second[i]+1]+=it.second.size()-i-1;
            V[it.second[i]+1]-=i;
        }
    }
    for(int i=1;i<=N;i++)V[i]+=V[i-1];
    for(int i=1;i<=N;i++)fprintf(g,"%d ",V[i]);
    fclose(f);
    fclose(g);
    return 0;
}
