#include <iostream>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
long long A[105];
long long B[105];
long long fst[105],s1;
long long snd[105],s2;
int F[105];
int S[105];
const int grup=100;
const int K=30000000/grup;
long long N,rez=1LL<<60;
void bulaneala()
{
    srand(time(NULL));
    N>>=1;
    for(long long i=1;i<=K;i++)
    {
        long long bestx,besty,minim=1LL<<62;
        for(int j=1;j<=grup;j++)
        {
            long long x,y;
            x=rand()%N+1;
            y=rand()%N+1;
            if(abs(s1-A[fst[x]]+A[snd[y]]-(s2-B[snd[y]]+B[fst[x]]))<minim)
            {
                minim=abs(s1-A[fst[x]]+A[snd[y]]-(s2-B[snd[y]]+B[fst[x]]));
                bestx=x;
                besty=y;
            }
        }
        if(minim<abs(s1-s2))
        {
            s1=s1-A[fst[bestx]]+A[snd[besty]];
            s2=s2-B[snd[besty]]+B[fst[bestx]];
            swap(fst[bestx],snd[besty]);
        }
    }
    cout<<abs(s1-s2)<<"\n";
    for(long long i=1;i<=N;i++)cout<<fst[i]<<" ";
    cout<<"\n";
    for(long long i=1;i<=N;i++)cout<<snd[i]<<" ";
}
struct data
{
    long long s;
    vector<int> pos;
};
bool cmp(data a,data b)
{
    return a.s<b.s;
}
unordered_map<int,vector<data> > st;
unordered_map<int,vector<data> > dr;
vector<int> V;
void gen(int l,int r,bool w)
{
    long long s1=0,s2=0;
    for(int conf=0;conf<1<<(N>>1);conf++)
    {
        V.clear();s1=s2=0;
        for(int j=0;j<(N>>1);j++)
        {
            if(conf&(1<<j))
            {
                V.push_back(l+j);
                s1+=A[l+j];
            }
            else
            {
                s2+=B[l+j];
            }
        }
        data tmp;
        tmp.s=s1-s2;
        tmp.pos=V;
        if(!w)st[(int)V.size()].push_back(tmp);
        else dr[(int)V.size()].push_back(tmp);
    }
}
bitset<105> U;
void mtm()
{
    long long rez=(1LL<<60);
    gen(1,N>>1,0);
    gen((N>>1)+1,N,1);
    int x,y,z;
    for(int i=0;i<=N/2;i++)
    {
       // sort(st[i].begin(),st[i].end(),cmp);
        sort(dr[i].begin(),dr[i].end(),cmp);
    }
    for(int i=0;i<=N/2;i++)
    {
        for(int j=0;j<st[i].size();j++)
        {
            auto it=st[i][j];
            int l=0,r=dr[N/2-i].size()-1;
            if(r<l)break;
            while(l<r)
            {
                int mid=(l+r+1)/2;
                if(dr[N/2-i][mid].s<=-it.s)l=mid;
                else r=mid-1;
            }
            if(abs(dr[N/2-i][l].s+it.s)<rez)
            {
                x=i;y=j;z=l;
                rez=abs(dr[N/2-i][l].s+it.s);
            }
            if(l<dr[N/2-i].size()-1&&abs(dr[N/2-i][l+1].s+it.s)<rez)
            {
                x=i;y=j;z=l+1;
                rez=abs(dr[N/2-i][l+1].s+it.s);
            }
        }
    }
    cout<<rez<<"\n";
    for(auto it:st[x][y].pos)
    {
        cout<<it<<" ";
        U[it]=1;
    }
    for(auto it:dr[N/2-x][z].pos)
    {
        cout<<it<<" ";
        U[it]=1;
    }
    cout<<"\n";
    for(int i=1;i<=N;i++)if(!U[i])cout<<i<<" ";
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(long long i=1;i<=N;i++)
    {
        cin>>A[i]>>B[i];
        if(snd[0]==N/2||((rand()&1)==0&&fst[0]<N/2)){fst[++fst[0]]=i;s1+=A[i];}
        else {snd[++snd[0]]=i;s2+=B[i];}
    }
    if(N<=36)
    {
        mtm();
    }
    else
        bulaneala();
    return 0;
}
