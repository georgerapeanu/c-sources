#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f=fopen("volei1.in","r");
FILE *g=fopen("volei1.out","w");
typedef pair<int,int> punct;
int F[2010],N,B[2010],M,st,nr,K,j,i;
punct C[2010];
vector <punct> V;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&F[i]);
        if(i-1)
            C[i]=punct(max(F[i-1],F[i]),i-1);

    }
    C[1]=punct(max(F[1],F[N]),N);
    fscanf(f,"%d",&M);
    for(i=1;i<=M;i++)
        fscanf(f,"%d",&B[i]);
    sort(C+1,C+1+N);
    sort(B+1,B+1+M);
    i=1;
    K=1;
    while(K<=N&&i<=M)
    {
        if(C[K].first<B[i])
        {
            V.push_back(punct(C[K].second,B[i]));
                        K++;
        }
        i++;
    }
    K--;
    sort(V.begin(),V.end());
    fprintf(g,"%d\n",K);
    for(i=1;i<=N;i++)
    {
        fprintf(g,"%d ",F[i]);
        if(V.size()>j&&V[j].first==i)
        {fprintf(g,"-%d ",V[j].second);j++;}
    }
    fclose(f);
    fclose(g);
    return 0;
}
