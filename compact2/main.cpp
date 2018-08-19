#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;
FILE *f=fopen("compact2.in","r");
//FILE *t=fopen("compact2.in","w");
FILE *g=fopen("compact2.out","w");
int V[1000001];
int col[1000001];
int poz[1000001];
int i,rez,N,j;
vector <int> tmp;
int main()
{
   /* for(i=0;i<20;i++)
    {
        tmp.push_back(i+1);
    }
    random_shuffle(tmp.begin(),tmp.end());
    fprintf(t,"20\n");
    for(i=0;i<20;i++)
        fprintf(t,"%d ",tmp[i]);
        */
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        poz[V[i]]=i;
    }
    for(i=N;i;i--)
    {
        col[i]=1;
        if(poz[V[i]-1]>i)
        {
            col[i]+=col[poz[V[i]-1]];
        }
        if(poz[V[i]+1]>i)
        {
            col[i]+=col[poz[V[i]+1]];
        }
        if(col[i]>rez)
            rez=col[i];
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}

