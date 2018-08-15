#include <cstdio>
#include <algorithm>
using namespace std;
int fr[20005];
int v;
long long rez,dif=1LL<<62;
int N;
int V[1000005];
int main()
{
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&V[i]);
        V[i]+=10000;
    }
    sort(V+1,V+1+N);
    scanf("%d",&v);
    v+=20000;
    for(int i=1;i<=N;i++)
    {
        if(V[i]>v)break;
        int st=0,dr=i-1;
        while(st<dr)
        {
            int mid=(st+dr+1)/2;
            if(V[mid]+V[i]<=v)st=mid;
            else dr=mid-1;
        }
        if(st)
        {
            if(dif>v-V[i]-V[st])
            {
                dif=v-V[i]-V[st];
                rez=fr[V[st]];
            }
            else if(dif==v-V[i]-V[st])
            {
                rez+=fr[V[st]];
            }
        }
        st=1;dr=i-1;
        while(st<dr)
        {
            int mid=(st+dr)/2;
            if(V[mid]+V[i]>v)
                dr=mid;
            else
                st=mid+1;
        }
        if(V[i]+V[st]>v)
        {
            if(dif>V[i]+V[st]-v)
            {
                dif=V[i]+V[st]-v;
                rez=fr[V[st]];
            }
            else if(dif==V[i]+V[st]-v)
            {
                rez+=fr[V[st]];
            }
        }
        fr[V[i]]++;
    }
    printf("%lld",rez);
    return 0;
}
