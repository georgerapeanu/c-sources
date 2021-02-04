#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class BipartiteMatcher{
    int n,m;
    int ans;
    vector<int> l;
    vector<int> r;
    vector<vector<int> > graph;
    vector<bool> viz;

    bool pairup(int nod){
        if(viz[nod] == true){
            return false;
        }
        viz[nod] = true;

        for(auto it:graph[nod]){
            if(r[it] == -1){
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

    BipartiteMatcher(int n,int m){
        this->n = n;
        this->m = m;
        l = vector<int>(n + 1,-1);
        r = vector<int>(m + 1, -1);
        graph = vector<vector<int> >(n + 1,vector<int>());
        viz = vector<bool>(n + 1,false);
        ans = 0;
    }

    void add_edge(int a,int b){
        graph[a].push_back(b);
    }
    
    int match(){
        bool ok = true;

        while(ok){
            ok = false;
    
            for(int i = 0; i < n;i++){
                viz[i] = false;
            }

            for(int i = 0;i < n;i++){
                if(l[i] == -1){
                    if(pairup(i)){
                        ans++;
                        ok = true;
                    }
                }
            }
        }

        return ans;
    }
};

const int NMAX = 500;

int n;
int d[NMAX + 5];

int main(){
    
    scanf("%d",&n);

    for(int i = 1; i <= n;i++){
        scanf("%d",&d[i]);
    }

    BipartiteMatcher solver(n,n);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            int c;
            scanf("%d",&c);

            if(i != j && d[i] + c <= d[j]){
                solver.add_edge(i - 1,j - 1);
            }
        }
    }

    printf("%d\n",n - solver.match());
    
    return 0;
}
