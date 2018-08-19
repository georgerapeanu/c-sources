#include <iostream>
#include <algorithm>
using namespace std;
int rez[3005];
int pre[3005][3005];
int N;
int a=0,b=0,c=0;
pair<int,int> V[3005];
int get(int st,int dr)
{
    return pre[st][dr];
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first;
        V[i].second=i;
    }
    sort(V+1,V+1+N);reverse(V+1,V+1+N);
    for(int i=1;i<=N;i++)
        for(int j=i;j<=N;j++)
            pre[i][j]=(V[pre[i][j-1]].first-V[pre[i][j-1]+1].first>V[j].first-V[j+1].first ? pre[i][j-1]:j);
    int lena,lenb,lencst,lencdr;
    for(int i=1;i<=N;i++)
    {
        lena=i;
        for(int j=i+1;j<=N;j++)
        {
            lenb=j-i;
            if(lena>2*lenb||lenb>2*lena)continue;
            lencst=max(lena,lenb)/2+max(lena,lenb)%2;
            lencdr=2*min(lena,lenb);
            if(lencdr<lencst||j+lencst>N)continue;
            int ind=get(j+lencst,min(j+lencdr,N));
               }
    }
    for(int i=1;i<=a;i++)rez[V[i].second]=1;
    for(int i=a+1;i<=b;i++)rez[V[i].second]=2;
    for(int i=b+1;i<=c;i++)rez[V[i].second]=3;
    for(int i=c+1;i<=N;i++)rez[V[i].second]=-1;
    for(int i=1;i<=N;i++)cout<<rez[i]<<" ";
    return 0;
}
