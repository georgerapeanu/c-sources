#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("restaurare.in","r");
FILE *g=fopen("restaurare.out","w");
typedef pair<int,int> data;
data L[100005],H[100005];
int i,j,N,Q,nr,fnr,k,rez[100005],maxim;
bool V[100005];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)   {fscanf(f,"%d",&L[i].first);L[i].second=i;if(L[i].first>maxim)maxim=L[i].first;}
    fscanf(f,"%d",&Q);
    for(i=1;i<=Q;i++) {fscanf(f,"%d",&H[i].first);H[i].second=i;}
    sort(L+1,L+1+N);
    sort(H+1,H+1+Q);
    j=1;k=1;
    for(i=1;i<=maxim;i++)
    {
        while(L[j].first<i)
        {
            V[L[j].second]=1;
            if(V[L[j].second+1]&&V[L[j].second-1])
                nr--;
            else if(V[L[j].second+1]||V[L[j].second-1])
                ;
            else
                nr++;
            j++;
        }
        fnr+=nr;
        while(H[k].first==i)
        {
            rez[H[k].second]=fnr;
            k++;
        }
    }
    for(i=1;i<=Q;i++)
        fprintf(g,"%d\n",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
