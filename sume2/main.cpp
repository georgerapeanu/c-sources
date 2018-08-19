#include <algorithm>
#include <cstdio>
using namespace std;
FILE *f=fopen("sume2.in","r");
FILE *g=fopen("sume2.out","w");
int V[50005];
long long K;
int N;
bool ch(int val)
{
    long long nr=0;
    for(int i=1;i<=N;i++)
    {
        int st=0,dr=N;
        while(st<dr)
        {
            int mid=(st+dr+1)/2;
            if(V[mid]+V[i]>val)
                dr=mid-1;
            else
                st=mid;
        }
        nr+=st;
    }
    return (nr>=K);
}
int main()
{
    fscanf(f,"%d%lld",&N,&K);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&V[i]);
    sort(V+1,V+1+N);
    int st=0,dr=(1<<21);
    while(st<dr)
    {
        int mid=(st+dr)/2;
        if(ch(mid))
            dr=mid;
        else
            st=mid+1;
    }
    fprintf(g,"%d",st);
    fclose(f);
    fclose(g);
    return 0;
}
