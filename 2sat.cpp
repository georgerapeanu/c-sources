#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("2sat.in","r");
FILE *g = fopen("2sat.out","w");

const int NMAX = 1e5;
const int OFFSET = NMAX + 3;

int ctc[2 * OFFSET + 5];
int ctc_gr[2 * OFFSET + 5];
vector<int> graph[2 * OFFSET + 5];
bool inst[2 * OFFSET + 5];
int st[2 * OFFSET + 5];
int len;
int id[2 * OFFSET + 5];
int low[2 * OFFSET + 5];
int last_id;
int last_ctc;
bool viz[2 * OFFSET + 5];
vector<int> ctc_nodes[2 * OFFSET + 5];

int gr_ctc[2 * OFFSET + 5];

void dfs(int nod) {
    st[++len] = nod;
    inst[nod] = true;
    id[nod] = ++last_id;
    low[nod] = id[nod];
    viz[nod] = true;

    for(auto it:graph[nod]) {
        if(viz[it] == false) {
            dfs(it);
        }
        if(inst[it] == true) {
            low[nod] = min(low[nod],low[it]);
        }
    }

    if(low[nod] == id[nod]) {
        last_ctc++;
        while(st[len] != nod) {
            ctc_nodes[last_ctc].push_back(st[len]);
            ctc[st[len]] = last_ctc;
            inst[st[len]] = false;
            len--;
        }
        ctc_nodes[last_ctc].push_back(st[len]);
        ctc[st[len]] = last_ctc;
        inst[st[len]] = false;
        len--;
    }
}

int n,m;

int ans[2 * OFFSET + 5];
int ctc_ans[2 * OFFSET + 5];

int main() {

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        graph[OFFSET - x].push_back(OFFSET + y);
        graph[OFFSET - y].push_back(OFFSET + x);
    }

    for(int i = OFFSET - n; i <= OFFSET + n; i++) {
        if(i == OFFSET) {
            continue;
        }
        if(viz[i] == false) {
            dfs(i);
        }
    }

    for(int i = 1; i <= last_ctc; i++) {
        ctc_ans[i] = -1;
        for(auto it:ctc_nodes[i]) {
            ans[it] = -1;
            for(auto it2:graph[it]) {
                if(ctc[it2] != i) {
                    ctc_gr[ctc[it2]]++;
                }
            }
        }
    }

    for(int i = 1 + OFFSET; i <= OFFSET + n; i++) {
        if(ctc[i] == ctc[2 * OFFSET - i]) {
            fprintf(g,"-1");
            return 0;
        }
    }

    vector<int> topo;

    for(int i = 1; i <= last_ctc; i++) {
        if(ctc_gr[i] == 0) {
            topo.push_back(i);
        }
    }

    for(int i = 0; i < (int)topo.size(); i++) {
        int val = ctc_ans[topo[i]];
        for(auto it:ctc_nodes[topo[i]]) {
            if(ans[it] != -1) {
                if(val == -1) {
                    val = ans[it];
                }
                else if(val != ans[it]) {
                    fprintf(g,"-1");
                    return 0;
                }
            }
        }

        val = max(val,0);

        ctc_ans[topo[i]] = val;

        for(auto it:ctc_nodes[topo[i]]) {
            ans[it] = val;
            ans[2 * OFFSET - it] = 1 - val;
            for(auto it2:graph[it]) {
                ctc_gr[ctc[it2]]--;
                if(ctc_gr[ctc[it2]] == 0) {
                    topo.push_back(ctc[it2]);
                    if(val == 1) {
                        if(ctc_ans[ctc[it2]] == 0) {
                            fprintf(g,"-1");
                            return 0;
                        }
                        ctc_ans[ctc[it2]] = 1;
                    }
                }
            }
        }
    }

    for(int i = OFFSET + 1; i <= OFFSET + n; i++) {
        if(ans[i] + ans[2 * OFFSET - i] != 1) {
            fprintf(g,"-1");
            return 0;
        }
    }

    for(int i = OFFSET + 1; i <= OFFSET + n; i++) {
        fprintf(g,"%d ",ans[i]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
