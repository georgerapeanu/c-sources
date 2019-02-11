#include<fstream>
#include<algorithm>
#include<vector>
#define F 20
using namespace std;

int dp[2][1<<F];
vector<pair<int,int>> v;

ifstream cin("fft2d.in");
ofstream cout("fft2d.out");

int main(){
    int f,t,i,j;
    cin>>f>>t;

    for(i=1;i<=t;i++){
        int a,b;
        cin>>a>>b;
        v.push_back({a,b});
    }

    sort(v.begin(),v.end());

    int k=0;
    for(i=0;i<f;i++){
        int b=(i&1);

        for(j=0;j<(1<<f);j++){
            if (k<v.size() &&v[k].first==i &&v[k].second==j){
                dp[b][j]=(1<<i);
                k++;
            }
            else dp[b][j]=dp[b^1][j]+dp[b^1][j^(1<<(f-1-i))];
        }
    }

    long long ans=(1LL<<(2*f-2));
    i=((f-1)&1);
    for(j=0;j<(1<<f);j++)
        ans-=dp[i][j];

    cout<<ans;
    return 0;
}
