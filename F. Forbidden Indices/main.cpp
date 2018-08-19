#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
int N;
string a,b;
int sa[200005];
int sum[200005];
int pos[200005];
int lcp[200005];
int tmp[200005];
int st[200005];
int dr[200005];
long long res;
stack<int> S;
int gap;
bool cmp(int i,int j)
{
    if(pos[i]!=pos[j])return pos[i]<pos[j];
    i+=gap;
    j+=gap;
    return i<=N&&j<=N ? pos[i]<pos[j]:i>j;
}
int main()
{
    cin>>N;
    cin>>a>>b;
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    a=" "+a;
    b=" "+b;
    for(int i=1;i<=N;i++)
    {
        sa[i]=i;
        pos[i]=a[i]-'a';
        if(b[i]!='1')res=max(res,(long long)N-i+1);
    }
    for(gap=1;gap<=N;gap<<=1)
    {
        sort(sa+1,sa+1+N,cmp);
        for(int i=1;i<N;i++)
            tmp[i+1]=tmp[i]+cmp(sa[i],sa[i+1]);
        for(int i=1;i<=N;i++)pos[sa[i]]=tmp[i];
    }
    for(int i=1;i<=N;i++)pos[sa[i]]=i;
    int k=0;
    for(int i=1;i<=N;i++)
    {
        if(pos[i]==N)
        {
            lcp[i]=0;
            k=0;
            continue;
        }
        int j=sa[pos[i]+1];
        while(i+k<=N&&j+k<=N&&a[i+k]==a[j+k])k++;
        lcp[pos[i]]=k;
        if(k)k--;
    }
    for(int i=1;i<=N;i++)
        sum[i]=sum[i-1]+(b[sa[i]]=='0');
    lcp[0]=lcp[N+1]=-1;
    S.push(0);
    for(int i=1;i<=N;i++)
    {
        while(lcp[i]<=lcp[S.top()])
        {
            int tmp=S.top();S.pop();
            res=max(res,1LL*lcp[tmp]*(sum[i]-sum[S.top()]));
        }
        S.push(i);
    }
    cout<<res;
    return 0;
}
