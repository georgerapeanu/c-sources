#include <cstdio>
#include <queue>
using namespace std;
FILE *f=fopen("secv.in","r");
FILE *g=fopen("secv.out","w");
int ind[1000005],N,i,S,K,cerinta,top,nr;
int V[1000005];
struct comp{
    bool operator()(int a,int b)
    {
        return ind[a]>ind[b];
    }
};
priority_queue <int,vector<int>,comp> H;
int main()
{
    fscanf(f,"%d%d%d%d",&cerinta,&N,&K,&S);
    if(cerinta==1)
    {
        for(i=1;i<=N;i++)
        {
            top++;
            fscanf(f,"%d",&ind[top]);
            ind[top]+=ind[top-1];
            if(top>=K&&ind[top]-ind[top-K]>S)
            {
                nr++;
                top-=K;
            }
        }
        fprintf(g,"%d",nr);
    }
    else
    {
        for(i=1;i<=N;i++)
        {
            fscanf(f,"%d",&ind[i]);
            V[i]=ind[i]+V[i-1];
            if(i>K)
            {
                while(!H.empty()&&V[i]-V[i-K-1]-ind[H.top()]>S)
                {
                    if(H.top()>=i-K)
                        {nr++;}
                    H.pop();
                }
            }
            H.push(i);
        }
        fprintf(g,"%d",nr);
    }
    fclose(f);
    fclose(g);
    return 0;
}
