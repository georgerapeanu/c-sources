#include <cstdio>
#include <vector>
#include <set>
#define x first
#define y second
using namespace std;
FILE *f=fopen("cutit.in","r");
FILE *g=fopen("cutit.out","w");
int K;
int N,M;
int nrnod;
void scrie(int st,int dr)
{
    for(int i=st;i<=dr;i++)
    {
        fprintf(g,"%d %d\n",1,i);
        for(int j=i+1;j<=dr;j++)
            fprintf(g,"%d %d\n",i,j);
    }
}
int main()
{
    fscanf(f,"%d",&K);
    for(int nrcomp=1;nrcomp<=80;nrcomp++)
    {
        int var=K+nrcomp;
        int nr=0;
        for(int i=0;i<14;i++)
            nr+=((var>>i)&1);
        if(nr<=nrcomp)
        {
            multiset<int> S;
            for(int i=0;i<14;i++)
                if((var>>i)&1)
                    S.insert(i);
            while(nr<nrcomp)
            {
                multiset<int>::iterator it=S.lower_bound(1);
                S.insert(*it-1);
                S.insert(*it-1);
                S.erase(it);
                nr++;
            }
            N++;
            for(auto i:S)
            {
                N+=i;
                M+=((i+1)*i)/2;
            }
            fprintf(g,"%d %d\n",N,M);
            int nrnod=1;
            for(auto i:S)
            {
                scrie(nrnod+1,nrnod+i);
                nrnod+=i;
            }
            return 0;
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
