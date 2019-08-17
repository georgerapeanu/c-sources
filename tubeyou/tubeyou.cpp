#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

FILE *f = fopen("tubeyou.in","r");
FILE *g = fopen("tubeyou.out","w");

const int NMAX = 25e4;
const int KMAX = 1e9;
const int LGMAX = 17;

long long init_d[NMAX + 5];///includes k for transitioning
long long curr_d[NMAX + 5];

int n,k,q;
int nxt[NMAX + 5];
vector<int> inv[NMAX + 5];
int wh_cycle[NMAX + 5];///cycle id on which this node is,if it is on any
int wh_comp[NMAX + 5];///the weakly-connected component in which this node is, it should be the same with the id of the cycle from the coresponding component
int wh_tree[NMAX + 5];///should be the same with the position in liniarizations

int viz[NMAX + 5];
int cyc[NMAX + 5],len_cycle;

vector<vector<int> > cycle;
vector<vector<int> > liniarization;///can be omitted,we don't need it,we just need the positions
///also second inclusion can be omitted
vector<int> lin;
int fst_pos[NMAX + 5];
int lst_pos[NMAX + 5];
int father[LGMAX + 1][NMAX + 5];
int lvl[NMAX + 5];

void dfs(int nod) {
    wh_tree[nod] = liniarization.size();
    lin.push_back(nod);
    fst_pos[nod] = (int)lin.size() - 1;
    for(auto it:inv[nod]) {
        wh_comp[it] = wh_comp[nod];
        father[0][it] = nod;
        lvl[it] = 1 + lvl[nod];
        dfs(it);
    }
    lin.push_back(-nod);///probably can be omitted
    lst_pos[nod] = (int)lin.size() - 1;
}

class AIB {
public:
    vector<long long> aib;

    AIB(int n) {
        aib.resize(n + 1);
    }

    void update(int pos,long long val) {
        for(; pos < (int)aib.size(); pos += (-pos) & pos) {
            aib[pos] += val;
        }
    }

    long long query(int pos) {
        long long ans = 0;
        for(; pos; pos -= (-pos) & pos) {
            ans += aib[pos];
        }
        return ans;
    }
};

vector<AIB> trees;///trees have the pourpose of moving nodes to their roots,they should not care about the state of the root,that's a cycle's job
vector<AIB> cycle_trees;

int lca(int x,int y) {
    if(lvl[y] < lvl[x]) {
        swap(x,y);
    }

    int delta = lvl[y] - lvl[x];

    for(int h = LGMAX; h >= 0; h--) {
        if((delta >> h) & 1) {
            y = father[h][y];
        }
    }

    if(x == y) {
        return x;
    }

    for(int h = LGMAX; h >= 0; h--) {
        if(father[h][x] != father[h][y]) {
            x = father[h][x];
            y = father[h][y];
        }
    }

    return father[0][x];
}

int find_first_undeleted(int x) {
    for(int h = LGMAX; h >= 0; h--) {
        int u = father[h][x];
        if(u > 0 && trees[wh_tree[x]].query(fst_pos[x]) == trees[wh_tree[x]].query(fst_pos[u] - 1)) {
            x = u;
        }
    }

    if(wh_cycle[x] == 0) {
        return father[0][x];
    }
    else if(curr_d[x] > 0) {
        return x;
    }

    if(cycle_trees[wh_cycle[x]].query(cycle[wh_cycle[x]].size()) > cycle_trees[wh_cycle[x]].query(viz[x])) { // is to the right
        int pos = 0;
        long long sum = 0;
        long long curr_sum = cycle_trees[wh_cycle[x]].query(viz[x]);
        for(int sh = 1 << LGMAX; sh; sh >>= 1) {
            if(pos + sh < (int)cycle_trees[wh_cycle[x]].aib.size() && sum + cycle_trees[wh_cycle[x]].aib[pos + sh] <= curr_sum) {
                pos |= sh;
                sum += cycle_trees[wh_cycle[x]].aib[pos];
            }
        }
        return cycle[wh_cycle[x]][pos + 1];
    }
    else { //is some pref
        int pos = 0;
        for(int sh = 1 << LGMAX; sh; sh >>= 1) {
            if(pos + sh < (int)cycle_trees[wh_cycle[x]].aib.size() && cycle_trees[wh_cycle[x]].aib[pos + sh] == 0) {
                pos += sh;
            }
        }
        return cycle[wh_cycle[x]][pos + 1];
    }
}

int main() {
    cycle.push_back(vector<int>());
    liniarization.push_back(vector<int>());

    fscanf(f,"%d %d %d",&n,&k,&q);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&nxt[i]);
        inv[nxt[i]].push_back(i);
    }

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%lld",&init_d[i]);
        init_d[i] += k;
        curr_d[i] = init_d[i];
    }

    //establishing cycles
    memset(viz,0,sizeof(viz));
    int lst_id = 0;
    for(int i = 1; i <= n; i++) {
        if(viz[i] == 0) {
            len_cycle = 0;
            int nod = i;
            while(viz[nod] == 0) {
                viz[nod] = ++len_cycle;
                cyc[len_cycle] = nod;
                nod = nxt[nod];
            }
            if(viz[nod] > len_cycle || cyc[viz[nod]] != nod) {
                continue;
            }
            ++lst_id;
            vector<int> tmp = {0};
            for(int j = viz[nod]; j <= len_cycle; j++) {
                wh_cycle[cyc[j]] = wh_comp[cyc[j]] = lst_id;
                tmp.push_back(cyc[j]);
            }
            cycle.push_back(tmp);
        }
    }

    //establishing components for subtrees, and erasing in cycle nodes from inverse

    ///erase from inverse
    for(int i = 1; i <= n; i++) {
        if(wh_cycle[i] > 0) {
            for(int j = 0; j < (int)inv[i].size(); j++) {
                if(wh_cycle[inv[i][j]] > 0) {
                    swap(inv[i][j],inv[i].back());
                    inv[i].pop_back();
                    break;
                }
            }
        }
    }

    ///propagating & liniarization
    for(int i = 1; i <= n; i++) {
        if(wh_cycle[i] > 0) {
            lin = {0};
            dfs(i);
            liniarization.push_back(lin);
        }
    }

    ///initializing aib for cylces
    ///iniitializing aib for linearization of trees
    ///wai de pula mea ce problema de cacat

    /* for(int i = 1;i <= n;i++){
         printf("%d %d\n",i,wh_tree[i]);
     }

     printf("lins:\n");

     for(auto it:liniarization){
         for(auto it2:it)printf("%d ",it2);
         printf("\n");
     }*/

    trees.push_back(AIB(0));
    for(int i = 1; i < (int)liniarization.size(); i++) {
        trees.push_back(AIB(liniarization[i].size()));
        for(int j = 1; j < (int)liniarization[i].size(); j++) {
            trees.back().update(j,(liniarization[i][j] < 0 ? -init_d[-liniarization[i][j]]:init_d[liniarization[i][j]]));
        }
    }

    cycle_trees.push_back(AIB(0));
    for(int i = 1; i < (int)cycle.size(); i++) {
        cycle_trees.push_back(AIB(cycle[i].size()));
        for(int j = 1; j < (int)cycle[i].size(); j++) {
            cycle_trees.back().update(j,init_d[cycle[i][j]]);
            viz[cycle[i][j]] = j;
        }
    }

    for(int h = 1; h <= LGMAX; h++) {
        for(int i = 1; i <= n; i++) {
            father[h][i] = father[h - 1][father[h - 1][i]];
        }
    }

    while(q--) {
        int t;
        fscanf(f,"%d",&t);
        if(t == 0) {
            int x;
            fscanf(f,"%d",&x);
            if(wh_cycle[x] > 0) { ///trees don't care about their roots
                int delta = 0 - curr_d[x];
                if(cycle_trees[wh_cycle[x]].query(cycle[wh_cycle[x]].size()) == curr_d[x]) {
                    continue;
                }
                cycle_trees[wh_cycle[x]].update(viz[x],delta);
                curr_d[x] = 0;
            }
            else {
                int delta = 0 - curr_d[x];
                curr_d[x] = 0;
                trees[wh_tree[x]].update(fst_pos[x],delta);
                trees[wh_tree[x]].update(lst_pos[x],-delta);
            }
        }
        else {
            int x,y;
            fscanf(f,"%d %d",&x,&y);
            long long ans = 0;
            long long off_x = 0;
            long long off_y = 0;
            if(x == y) {
                ans = 0;
            }
            else {
                if(curr_d[x] == 0) {
                    off_x = init_d[x];
                    x = find_first_undeleted(x);
                }
                if(curr_d[y] == 0) {
                    off_y = init_d[y];
                    y = find_first_undeleted(y);
                }
                if(wh_comp[x] != wh_comp[y]) {
                    ans = 1e18;
                }
                else if(wh_tree[x] == wh_tree[y]) {
                    int u = lca(x,y);
                    ans = max(trees[wh_tree[x]].query(fst_pos[x]) + off_x,trees[wh_tree[y]].query(fst_pos[y]) + off_y) - trees[wh_tree[x]].query(fst_pos[u]);
                }
                else {
                    long long ans_x = off_x;
                    long long ans_y = off_y;
                    int root_x = liniarization[wh_tree[x]][1];
                    int root_y = liniarization[wh_tree[y]][1];

                    ans_x += trees[wh_tree[x]].query(fst_pos[x]) - trees[wh_tree[x]].query(1);
                    ans_y += trees[wh_tree[y]].query(fst_pos[y]) - trees[wh_tree[y]].query(1);

                    if(viz[root_x] > viz[root_y]) {
                        swap(root_x,root_y);
                        swap(ans_x,ans_y);
                        swap(x,y);
                    }

                    long long transit_xy = cycle_trees[wh_cycle[root_y]].query(viz[root_y] - 1) - cycle_trees[wh_cycle[root_x]].query(viz[root_x] - 1);
                    long long transit_yx = cycle_trees[wh_cycle[root_y]].query(cycle[wh_cycle[root_y]].size()) - (cycle_trees[wh_cycle[root_y]].query(viz[root_y] - 1) - cycle_trees[wh_cycle[root_x]].query(viz[root_x] - 1));

                    ans = max(min(ans_x + transit_xy,ans_y + transit_yx),max(ans_x,ans_y));
                }
            }
            fprintf(g,"%lld\n",ans);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
