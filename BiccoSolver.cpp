#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("biconex.in","r");
FILE *g = fopen("biconex.out","w");

const int NMAX = 1e5;
const int MMAX = 2e5;

///0 indexed;
class BiccoSolver {
private:
    int n;
    vector<int> id;
    vector<int> low;
    int last_id;
    vector<pair<int,int> > st;
    vector<vector<int>> ans;

    void dfs(int nod,int tata,const vector<vector<int>> &graph) {
        low[nod] = id[nod] = ++last_id;

        for(auto it:graph[nod]) {
            if(it == tata) {
                continue;
            }

            if(id[it]) {
                low[nod] = min(low[nod],id[it]);
            }
            else {
                st.push_back({it,nod});
                dfs(it,nod,graph);
                low[nod] = min(low[nod],low[it]);
                if(low[it] >= id[nod]) {
                    vector<int> v;
                    while(st.back() != make_pair(it,nod)) {
                        v.push_back(st.back().first);
                        v.push_back(st.back().second);
                        st.pop_back();
                    }
                    v.push_back(st.back().first);
                    v.push_back(st.back().second);
                    st.pop_back();

                    sort(v.begin(),v.end());
                    v.resize(unique(v.begin(),v.end()) - v.begin());
                    ans.push_back(v);
                }
            }
        }
    }

public:

    BiccoSolver(int n) {
        this->n = n;
        this->id = vector<int>(n,0);
        this->low = vector<int>(n,0);
        this->last_id = 0;
        this->st.clear();
        this->ans.clear();
    }

    vector< vector<int> > solve(const vector<vector<int>> &graph) {
        this->id = vector<int>(n,0);
        this->last_id = 0;
        this->st.clear();
        this->ans.clear();
        dfs(0,-1,graph);
        return ans;
    }
};

int main() {

    int n,m;

    fscanf(f,"%d %d",&n,&m);

    vector<vector<int> > graph(n,vector<int>());

    BiccoSolver a(n);

    for(int i = 1; i <= m; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        x--;
        y--;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    vector<vector<int> > bicco = a.solve(graph);

    fprintf(g,"%d\n",(int)bicco.size());

    for(auto it:bicco) {
        for(auto it2:it) {
            fprintf(g,"%d ",it2 + 1);
        }
        fprintf(g,"\n");
    }

    return 0;
}
