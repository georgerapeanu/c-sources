#include <cstdio>
#include <set>
using namespace std;
set <long long> S[2505];
set <int> A[2505];
FILE *f=fopen("matriosca.in","r");
FILE *g=fopen("matriosca.out","w");
int N,i,ctr=0,j,x;
long long a;
int main()
{
    fscanf(f,"%d",&N);
    S[0].insert(20000000000);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&a);
        x=0;
        for(j=1;j<=ctr;j++)
        {
            if(a<*(S[j].begin()))
            {
                if(*(S[j].begin())<*(S[x].begin()))
                    x=j;
            }
        }
        if(!x)
        {
            ctr++;
            S[ctr].insert(a);
            A[ctr].insert(i);
        }
        else
            {
                S[x].insert(a);
                A[x].insert(i);
            }
    }
    fprintf(g,"%d\n",ctr);
    for(i=1;i<=ctr;i++)
    {
        fprintf(g,"%d ",A[i].size());
        for(set<int>::iterator it=A[i].begin();it!=A[i].end();it++)
        {
            fprintf(g,"%d ",*it);
        }
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
