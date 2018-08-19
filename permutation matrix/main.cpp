#include <iostream>
#include <bitset>
using namespace std;
bitset<100005> viz1,viz2;
long long scic[100005],sucic[100005],ucic[100005];
int lcic[100005],l;
int P[100005];
int T[100005];
int s;
int N,M;
void dfs1(int nod)
{
    viz1[nod]=1;
    s+=nod;
    l++;
    if(viz1[P[nod]]==0)dfs1(P[nod]);
}
void dfs2(int nod)
{
    viz2[nod]=1;
    scic[nod]=s;
    lcic[nod]=l;
    if(viz2[P[nod]]==0) dfs2(P[nod]);
    ucic[nod]=T[ucic[P[nod]]];
    sucic[nod]=sucic[P[nod]]-ucic[P[nod]]+P[nod];
}
int main() {
    cin>>M>>N;
    for(int i=1;i<=M;i++)
        {cin>>P[i];T[P[i]]=i;}
    for(int i=1;i<=M;i++)
    {
        if(viz1[i]==0)
        {
            s=0;
            l=0;
            dfs1(i);
            viz2[i]=1;
            scic[i]=s;
            lcic[i]=l;
            int nod,l;
            for(nod=P[i], l=N%lcic[i];l;l--,nod=P[nod])
            {
                ucic[i]=nod;
                sucic[i]+=nod;
            }
            dfs2(P[i]);
        }
    }
    for(int i=1;i<=M;i++)
    {
        cout<<(N/lcic[i])*scic[i]+(N%lcic[i]!=0)*sucic[i]<<" ";
    }
    return 0;
}
