#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("multiplu.in","r");
FILE *g=fopen("multiplu.out","w");
int N,M,i;
int V[2005],a,b,c,d,e,q,j,st,dr,val;
pair<int,int> A[2005];
int mid,last;
bool ok;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        A[i].first=V[i]%M;
        A[i].second=V[i]/M;
    }
    sort(A+1,A+1+N);
    sort(V+1,V+1+N);
    for(i=1;i<=N&&!ok;i++)
    {
        for(j=i+1;j<=N&&!ok;j++)
        {
            st=1;
            dr=N;
            last=-1;
            val=M-((V[i]+V[j])%M);
            while(st<=dr)
            {
                mid=(st+dr)/2;
                if(A[mid].first<=val)
                {
                    last=mid;
                    st=mid+1;
                }
                else
                    dr=mid-1;
            }
            if(last!=-1)
            {
                if(A[last].first==val)
                {
                    while(A[last-1].first==val)
                        last--;
                    if(A[last].second*M+A[last].first==i)
                    {
                        last++;
                        if(A[last].second*M+A[last].first==j)
                            last++;
                    }
                    else if(A[last].second*M+A[last].first==j)
                    {
                        last++;
                        if(A[last].second*M+A[last].first==i)
                            last++;
                    }
                    if(A[last].first==val)
                    {
                    ok=1;
                    a=V[i];
                    b=V[j];
                    c=last;
                    }
                }
            }
        }
    }
    c=A[c].second*M+A[c].first;
    d=max(max(a,b),c);
    e=min(min(a,b),c);
    q=d^e^a^b^c;
    if(ok)
        fprintf(g,"%d %d %d",e,q,d);
    else
        fprintf(g,"0");
    fclose(f);
    fclose(g);
    return 0;
}
