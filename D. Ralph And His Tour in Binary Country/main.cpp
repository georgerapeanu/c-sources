#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct query
{
    int ind;
    int H;
    bool operator <(const query &other)const
    {
        return H<other.H;
    }
};
struct node
{
    vector<query> Qst,Qdr;
    vector<int> nrnodst,nrnoddr;
    vector<long long> Lst,Ldr;
}V[1000005];
int L[1000005];
int N,M;
long long R[1000005];
bool testCorectPropagation=0;
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin>>N>>M;
    for(int i=2;i<=N;i++)
    {
        cin>>L[i];
    }
    for(int i=1;i<=M;i++)
    {
        int A,H;
        cin>>A>>H;
        V[A].Qst.push_back({i,H});
        V[A].Qdr.push_back({i,H});
        R[i]-=H;
        while(A!=1&&H>=L[A])
        {
            H-=L[A];
            if(A%2==1)V[A/2].Qdr.push_back({i,H});
            else V[A/2].Qst.push_back({i,H});
            A/=2;
        }
    }
    for(int i=1;i<=N;i++)
    {
        sort(V[i].Qst.begin(),V[i].Qst.end());
        sort(V[i].Qdr.begin(),V[i].Qdr.end());
        V[i].nrnodst.resize(V[i].Qst.size());V[i].Lst.resize(V[i].Qst.size());
        V[i].nrnoddr.resize(V[i].Qdr.size());V[i].Ldr.resize(V[i].Qdr.size());
    }
    for(int i=1;i<=N;i++)
    {
        if(V[i].Lst.size()){V[i].Lst[0]+=0;V[i].nrnodst[0]++;}
        if(V[i].Ldr.size()){V[i].Ldr[0]+=0;V[i].nrnoddr[0]++;}
        int A=i,l=0;
        while(A!=1)
        {
            l+=L[A];
            if(A%2==0)
            {
                int st=-1,dr=V[A/2].Qdr.size();
                while(dr-st>1)
                {
                    int mid=(st+dr)/2;
                    if(V[A/2].Qdr[mid].H>=l)
                        dr=mid;
                    else
                        st=mid;
                }
                if(dr!=V[A/2].Qdr.size())
                {
                    V[A/2].Ldr[dr]+=l;
                    V[A/2].nrnoddr[dr]++;
                }
            }
            else
            {
                int st=-1,dr=V[A/2].Qst.size();
                while(dr-st>1)
                {
                    int mid=(st+dr)/2;
                    if(V[A/2].Qst[mid].H>=l)
                        dr=mid;
                    else
                        st=mid;
                }
                if(dr!=V[A/2].Qst.size())
                {
                    V[A/2].Lst[dr]+=l;
                    V[A/2].nrnodst[dr]++;
                }
            }
            A>>=1;
        }
    }
    for(int i=1;i<=N;i++)
    {
        int nodes=0;
        long long l=0;
        for(int j=0;j<V[i].Qst.size();j++)
        {
            nodes+=V[i].nrnodst[j];
            l+=V[i].Lst[j];
            R[V[i].Qst[j].ind]+=1LL*nodes*V[i].Qst[j].H-l;
        }
        nodes=0;
        l=0;
        for(int j=0;j<V[i].Qdr.size();j++)
        {
            nodes+=V[i].nrnoddr[j];
            l+=V[i].Ldr[j];
            R[V[i].Qdr[j].ind]+=1LL*nodes*V[i].Qdr[j].H-l;
        }
    }
    for(int i=1;i<=M;i++)
        cout<<R[i]<<"\n";
    return 0;
}
