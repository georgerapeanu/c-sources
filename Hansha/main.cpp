#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
FILE *f=fopen("hansha.in","r");
FILE *g=fopen("hansha.out","w");
int L[32];
int T,K;
int A,B;
map<pair<pair<int,int>,int>,int> rez;
int solve(int k,int a,int b)
{
    if(a>b)swap(a,b);
    if(a==b||k==0)return 0;
    if(rez[{{k,a},b}])return rez[{{k,a},b}];
    if(b<=(1<<(k-1)))return rez[{{k,a},b}]=solve(k-1,a,b);
    else if(a>(1<<(k-1)))return rez[{{k,a},b}]=solve(k-1,a-(1<<(k-1)),b-(1<<(k-1)));
    return rez[{{k,a},b}]=solve(k-1,a,L[k])+1+solve(k-1,L[k],b-(1<<(k-1)));
}
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        rez.clear();
        fscanf(f,"%d",&K);
        for(int i=1;i<=K;i++)fscanf(f,"%d",&L[i]);
        fscanf(f,"%d %d",&A,&B);
        fprintf(g,"%d\n",solve(K,A,B));
    }
    fclose(f);
    fclose(g);
    return 0;
}
