#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e4;

class BipartiteMatcher{
    
    int n;
    vector<vector<int>> graph;
    vector<int> l;
    vector<int> r;
    vector<int> viz;

    bool pairup(int nod){
        if(viz[nod]){
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

public:

    BipartiteMatcher(int n){
        this->n = n;
        graph = vector<vector<int>>(n + 1);
        l = vector<int>(n + 1);
        r = vector<int>(n + 1);
        viz = vector<int>(n + 1);
    }

    void add_edge(int a,int b){
        graph[a].push_back(b);
    }

    int solve(){
        l = vector<int>(n + 1,0);
        r = vector<int>(n + 1,0);

        int ans = 0;
        bool ok = true;

        while(ok){
            ok = false;
            viz = vector<int>(n + 1,0);

            for(int i = 1;i <= n;i++){
                if(l[i] == 0 && pairup(i)){
                    ok = true;
                    ans++;
                }
            }
        }

        return ans;
        
    }
};

int n;

int main(){

    scanf("%d",&n);

    BipartiteMatcher solver(n);

    for(int i = 1;i <= n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        solver.add_edge(x,y);
    }

    printf("%d\n",solver.solve());
   
    return 0;
}
