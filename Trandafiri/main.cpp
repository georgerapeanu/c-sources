#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("trandafiri.in","r");
FILE *g=fopen("trandafiri.out","w");
long long maxi,mini=1LL<<60;
long long val;
int N;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&val);
        mini=min(mini,val);
        maxi=max(maxi,val);
    }
    fprintf(g,"%lld\n",maxi-mini+N-1);
    fclose(f);
    fclose(g);
    return 0;
}
