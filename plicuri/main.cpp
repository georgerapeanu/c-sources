#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("plicuri.in","r");
FILE *g=fopen("plicuri.out","w");
pair<int,int> P[100005];
int len;
int B[100005];
int N;
bool cmp(pair<int,int> a,pair<int,int> b)
{
    if(a.first!=b.first)
        return a.first<b.first;
    return a.second>b.second;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&P[i].first,&P[i].second);
        if(P[i].first>P[i].second)
            swap(P[i].first,P[i].second);
    }
    sort(P+1,P+1+N,cmp);
    for(int i=1;i<=N;i++)
    {
        int st=0;
        int dr=len;
        while(st<dr)
        {
            int mid=(st+dr+1)/2;
            if(B[mid]<P[i].second)
                st=mid;
            else
                dr=mid-1;
        }
        if(st==len)
        {
            B[++len]=P[i].second;
        }
        else if(B[st+1]>P[i].second)
            B[st+1]=P[i].second;
    }
    fprintf(g,"%d",len);
    fclose(f);
    fclose(g);
    return 0;
}
