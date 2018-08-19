#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f=fopen("timp.in","r");
FILE *g=fopen("timp.out","w");
long long N,K;
vector<int> V;
int main()
{
    fscanf(f,"%lld %lld",&N,&K);
    while(K&&K!=N)
    {
        if(2*K>=N)
        {
            K=2*K-N;
            V.push_back(0);
        }
        else
        {
            K=2*K;
            V.push_back(1);
        }
    }
    reverse(V.begin(),V.end());
    fprintf(g,"%d\n",V.size());
    int val=0;
    for(auto it:V)
    {
        val^=1;
        fprintf(g,"%d\n",val^it);
    }
    fclose(f);
    fclose(g);
    return 0;
}
