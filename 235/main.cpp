#include <cstdio>
#include <vector>
#include <set>
using namespace std;
FILE *f=fopen("235.in","r");
FILE *g=fopen("235.out","w");
vector <int> V;
set <int> val3;
set <int> val5;
int N,nr,i,j;
int main()
{
    fscanf(f,"%d",&N);
    V.push_back(0);
    nr=1;
    while(nr<=2000000000)
    {
        val3.insert(nr);
        nr*=3;
    }
    nr=1;
    while(nr<=2000000000)
    {
        val5.insert(nr);
        nr*=5;
    }
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&nr);
        if(val3.find(nr)!=val3.end())
            V.push_back(V[V.size()-1]+1);
        else if(val5.find(nr)!=val5.end())
            V.push_back(V[V.size()-1]-1);
    }
    N=V.size()-1;
    fprintf(g,"%d\n",N);
    nr=0;
    for(i=1;i<=N;i++)
    {
        for(j=2;j+i-1<=N;j*=2)
        {
            if(V[j+i-1]-V[i-1]==0)
                nr++;
        }
    }
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
