#include <algorithm>
#include <cstdio>
using namespace std;
FILE *f=fopen("sume2.in","r");
FILE *g=fopen("sume2.out","w");
int V[50005];
int K;
int N;
bool ch(int val)
{
    int nr;
    for(int i=1;i<=N;i++)
    {
        int st=1,dr=N;
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
    fscanf(f,"%d%d",&N,&K);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&V[i]);
    sort(V+1,V+1+N);
    int st=1,dr=(1<<21);
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
