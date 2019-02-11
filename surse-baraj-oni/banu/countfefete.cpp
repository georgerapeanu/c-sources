#include <fstream>
#include <vector>
#define Nmax 200002
#define MOD 1000000007
using namespace std;

ifstream f("countfefete.in");
ofstream g("countfefete.out");

int n,val[Nmax],x,y,uz[Nmax],nrv[Nmax],nrv2[Nmax],viz[Nmax];
int ans;

vector<int> v[Nmax];

vector<int> H;

int dfs(int nod,int ant){
    int keep = uz[nod];
    for (auto it : v[nod]){
        if (it==ant) continue;
        keep |= dfs(it,nod);
    }
    if (keep) viz[nod] = 1;
    return keep;
}

int getMN(){
    int ans = 1e9;
    int sav = 0;
    for (int i=1;i<=n;i++){
        viz[i] = 0;
        if (uz[i]) sav = i;
    }

    dfs(sav,-1);

    for (int i=1;i<=n;i++) if (viz[i]) ans = min(ans,val[i]);

    return ans;
}

int main()
{
    f>>n;
    for (int i=1;i<=n;i++) f>>val[i];
    for (int i=1;i<n;i++){
        f>>x>>y;
        v[x].push_back(y);
        nrv[x]++;
        v[y].push_back(x);
        nrv[y]++;
    }

    int mx = (1<<n);

    for (int i=1;i<mx;i++){
        int aux = 0;
        for (int j=0;j<n;j++){
            if ((1<<j) & i) uz[j+1] = 1, aux ^= (val[j+1]);
            else uz[j+1] = 0;
        }
        aux ^= getMN();
        ans += aux;
        if (ans>MOD) ans -= MOD;
    }

    g<<ans;

    return 0;
}
