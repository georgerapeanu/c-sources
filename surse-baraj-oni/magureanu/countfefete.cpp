#include<fstream>
#include<algorithm>
#include<vector>
#include<bitset>
#define M 1000000007
#define N 200000
#define B 30
using namespace std;

class mazi{
public:
    int cnt;
    int ans[B];

    mazi(){
        cnt=0;
        for(int i=0;i<B;i++)
            ans[i]=0;
    }
};

mazi dp[N+1];
pair<int,int> v[N+1];
vector<int> vecin[N+1];

int tata[N+1];
bitset<N+1> viz;

int rad(int x){
    if (tata[x]==0) return x;
    tata[x]=rad(tata[x]);
    return tata[x];
}

ifstream cin("countfefete.in");
ofstream cout("countfefete.out");

bool meow(pair<int,int> a,pair<int,int> b){
    return (a.first>b.first);
}

int put2[N+1];

void prec(int n){
    put2[0]=1;
    for(int i=1;i<=n;i++)
        put2[i]=(put2[i-1]*2)%M;
}

int ansgl;

int main(){
    int n,i,j;
    cin>>n;

    for(i=1;i<=n;i++){
        cin>>v[i].first;
        v[i].second=i;

        dp[i].cnt=1;
        for(j=0;j<B;j++)
            dp[i].ans[j]=((v[i].first>>j)&1);
    }

    for(i=1;i<n;i++){
        int a,b;
        cin>>a>>b;

        vecin[a].push_back(b);
        vecin[b].push_back(a);
    }

    sort(v+1,v+n+1,meow);
    prec(n);

    for(i=1;i<=n;i++){
        int nod=v[i].second;
        int mini=v[i].first;
        viz.set(nod);

        for(j=0;j<vecin[nod].size();j++){
            int now=vecin[nod][j];
            if (viz[now]==true){
                now=rad(now);

                for(int l=0;l<30;l++){
                    if ((mini&(1<<l))==0) ansgl=(ansgl+((1LL<<l)*((1LL*dp[nod].ans[l]*(put2[dp[now].cnt]-1-dp[now].ans[l]+M))%M+(1LL*dp[now].ans[l]*(put2[dp[nod].cnt]-1-dp[nod].ans[l]+M))%M)%M))%M;
                    else ansgl=(ansgl+(1LL<<l)*(((1LL*dp[nod].ans[l]*dp[now].ans[l])%M+(1LL*(put2[dp[nod].cnt]-1-dp[nod].ans[l]+M)*(put2[dp[now].cnt]-1-dp[now].ans[l]+M))%M)%M))%M;
                    dp[nod].ans[l]=((1LL*dp[nod].ans[l]*(put2[dp[now].cnt]-dp[now].ans[l]+M))%M+(1LL*dp[now].ans[l]*(put2[dp[nod].cnt]-dp[nod].ans[l]+M))%M)%M;
                }

                dp[nod].cnt+=dp[now].cnt;
                tata[now]=nod;
            }
        }
    }

    cout<<ansgl;
    return 0;
}
