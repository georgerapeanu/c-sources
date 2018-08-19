#include <cstdio>
#include <unordered_map>
using namespace std;
FILE *f=fopen("pariuri.in","r");
FILE *g=fopen("pariuri.out","w");
long long bani;
int timp;
unordered_map<int,long long> V;
int N,M;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&M);
        for(int j=1;j<=M;j++)
            {fscanf(f,"%d%lld",&timp,&bani);V[timp]+=bani;}
    }
    fprintf(g,"%d\n",V.size());
    for(auto it:V)
        fprintf(g,"%d %d ",it.first,it.second);
    fclose(f);
    fclose(g);
    return 0;
}
