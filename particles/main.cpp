#include <iostream>
#include <algorithm>

using namespace std;
int N,L,K;
struct particle
{
    int t,v,ind;
    bool operator <(const particle &other) const
    {
        if(t!=other.t)return t<other.t;
        return v>other.v;
    }
    long double better(const particle &other)
    {
        if(t<other.t)return 0;
        if(v<=other.v)return 5e18;
        return t+((long double)(t-other.t)*other.v)/(v-other.v);
    }
}A[50005],B[50005];
int sz1,sz2;
particle V1[50005];
particle V2[50005];
bool U1[50005];
bool U2[50005];
long double intersect(particle a,particle b)
{
    return ((long double)L+b.v*b.t+a.v*a.t)/(a.v+b.v);
}
int main() {
    cin>>N>>L>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i].t>>A[i].v;
        A[i].ind=i;
    }
    for(int i=1;i<=N;i++)
    {
        cin>>B[i].t>>B[i].v;
        B[i].ind=i;
    }
    sort(A+1,A+1+N);
    sort(B+1,B+1+N);
    while(K--)
    {
        sz1=sz2=0;
        for(int i=1;i<=N;i++)
        {
            if(!U1[A[i].ind])
            {
                if(sz1&&A[i].better(V1[sz1])==5e18)continue;
                while(sz1>1&&A[i].better(V1[sz1])<=V1[sz1].better(V1[sz1-1]))
                    sz1--;
                V1[++sz1]=A[i];
            }
        }
        for(int i=1;i<=N;i++)
        {
            if(!U2[B[i].ind])
            {
                if(sz2&&B[i].better(V2[sz2])==5e18)continue;
                while(sz2>1&&B[i].better(V2[sz2])<=V2[sz2].better(V2[sz2-1]))sz2--;
                V2[++sz2]=B[i];
            }
        }
        for(int i=1;i<=sz1;i++)cerr<<V1[i].better(V1[i-1])<<" ";cerr<<"\n";
        for(int i=1;i<=sz2;i++)cerr<<V2[i].better(V2[i-1])<<" ";cerr<<"\n\n";
        int i=1,j=1;
        for(int k=1;k<=sz1+sz2;k++)
        {
            if(intersect(V1[i],V2[j])<=min((i==sz1 ? 5e18:V1[i+1].better(V1[i])),(j==sz2 ? 5e18:V2[j+1].better(V2[j]))))
            {
                U1[V1[i].ind]=1;
                U2[V2[j].ind]=1;
                cout<<V1[i].ind<<" "<<V2[j].ind<<"\n";
                break;
            }
            if(i==sz1)j++;
            else if(j==sz2)i++;
            else
            {
                if(V1[i+1].better(V1[i])<V2[j+1].better(V2[j]))i++;
                else j++;
            }
        }
    }
    return 0;
}
