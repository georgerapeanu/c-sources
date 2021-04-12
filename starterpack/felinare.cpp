#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e4;

int n,m;
vector<int> graph[NMAX + 5];
int l[NMAX + 5];
int r[NMAX + 5];
int in_cover[2 * NMAX + 5];
bool viz[NMAX + 5];

bool pairup(int nod){
    if(viz[nod] == true){
        return false;
    }
    viz[nod] = true;

    for(auto it:graph[nod]){
        if(r[it] == 0){
            l[nod] = it;
            r[it] = nod;
            return true;
        }
    }

    for(auto it:graph[nod]){
        if(pairup(r[it])){
            l[nod] = it;
            r[it] = nod;
            return true;
        }
    }

    return false;
}

int match(){
    int ans = 0;
    bool ok = true;

    while(ok){
        for(int i = 1;i <= n;i++){
            viz[i] = false;
        }
        ok = false;
        for(int i = 1;i <= n;i++){
            if(l[i] == 0 && pairup(i)){
                ok = true;
                ans++;
            }
        }
    }

    return ans;
}

void vertex_cover(int nod){
    if(viz[nod]){
        return ;
    }
    viz[nod] = true;

    for(auto it:graph[nod]){
        if(in_cover[n + it] == false){
            in_cover[r[it]] = false;
            in_cover[n + it] = true;
            vertex_cover(r[it]);
        }
    }
}

int main(){
   
    freopen("felinare.in","r",stdin);
    freopen("felinare.out","w",stdout);

    scanf("%d %d",&n,&m);

    while(m--){
        int a,b;
        scanf("%d %d",&a,&b);
        graph[a].push_back(b);
    }

    int ans = 2 * n - match();

    for(int i = 1;i <= n;i++){
        viz[i] = false;
        if(l[i]){
            in_cover[i] = true;
        }
    }

    for(int i = 1;i <= n;i++){
        if(l[i] == 0){
            vertex_cover(i);
        }
    }

    printf("%d\n",ans);

    for(int i = 1;i <= n;i++){
        printf("%d\n",((!in_cover[i]) << 0) | ((!in_cover[i + n]) << 1));
    }


    return 0;
}
