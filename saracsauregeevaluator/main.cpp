#include <cstdio>
#include <algorithm>
#include <ctime>
using namespace std;
pair<int,int> V[1000005];
int X[1000005];
int RMQ[50005][20],lg[10000005];
int N,M;
bool cmp(pair<int,int> a,pair<int,int> b)
{
    return a.second-a.first>b.second-b.first;
}
int main()
{
    FILE *f=fopen("1.in","w"),*g=fopen("1.out","w");
    N=50000;
    M=50000;
    fprintf(f,"%d %d\n",N,M);
    for(int i=1;i<=N;i++)
    {
        fprintf(f,"%d ",N-i+1);
    }
    fprintf(g,"\n");
    for(int i=1;i<=M;i++)
        fprintf(f,"%d %d\n",i,M);
    return 0;
}
