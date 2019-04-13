#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("party.in","r");
FILE *g = fopen("party.out","w");

const int NMAX = 1e2;
const int OFFSET = NMAX + 2;

vector<int> graph[2 * OFFSET + 5];

int n,m;
bool viz[2 * OFFSET + 5];
int st[2 * OFFSET + 5],len;
bool inst[2 * OFFSET + 5];
int ctc[2 * OFFSET + 5],last_ctc;
int id[2 * OFFSET + 5],last_id;
int low[2 * OFFSET + 5];
vector<int> ctc_nodes[2 * OFFSET + 5];

void dfs(int nod) {
    viz[nod] = true;
    st[++len] = nod;
    inst[nod] = true;
    id[nod] = low[nod] = ++last_id;

    for(auto it:graph[nod]) {
        if(viz[it] == false) {
            dfs(it);
        }
        if(inst[it]) {
            low[nod] = min(low[nod],low[it]);
        }
    }

    if(low[nod] == id[nod]) {
        last_ctc++;
        while(st[len] != nod) {
            ctc[st[len]] = last_ctc;
            ctc_nodes[last_ctc].push_back(st[len]);
            inst[st[len]] = false;
            len--;
        }
        ctc[st[len]] = last_ctc;
        ctc_nodes[last_ctc].push_back(st[len]);
        inst[st[len]] = false;
        len--;
    }
}

int ans[2 * OFFSET + 5];
int ctc_ans[2 * OFFSET + 5];
int ctc_gr[2 * OFFSET + 5];

vector<int> solve_clauses() {
    for(int i = OFFSET - n; i <= OFFSET + n; i++) {
        if(i == OFFSET) {
            continue;
        }
        ans[i] = -1;
        if(viz[i] == false) {
            dfs(i);
        }
    }

    for(int i = 1; i <= last_ctc; i++) {
        ctc_ans[i] = -1;
    }

    for(int i = OFFSET - n; i <= OFFSET + n; i++) {
        if(i == OFFSET) {
            continue;
        }
        for(auto it:graph[i]) {
            if(ctc[it] != ctc[i]) {
                ctc_gr[ctc[it]]++;
            }
        }
    }

    vector <int> topo;

    for(int i = 1; i <= last_ctc; i++) {
        if(ctc_gr[i] == 0) {
            topo.push_back(i);
        }
    }

    for(int i = 0; i < (int)topo.size(); i++) {
        int comp = topo[i];
        int val = ctc_ans[comp];

        for(auto it:ctc_nodes[comp]) {
            val = max(val,ans[it]);
        }

        val = max(val,0);

        ctc_ans[comp] = val;

        for(auto it:ctc_nodes[comp]) {
            ans[it] = val;
            ans[2 * OFFSET - it] = 1- val;
            for(auto it2:graph[it]) {
                if(ctc[it2] != ctc[it]) {
                    ctc_gr[ctc[it2]]--;
                    if(ctc_gr[ctc[it2]] == 0) {
                        topo.push_back(ctc[it2]);
                    }
                    if(val == 1) {
                        ctc_ans[ctc[it2]] = 1;
                    }
                }
            }
        }
    }

    vector<int> cnt;

    for(int i = OFFSET + 1; i <= OFFSET + n; i++) {
        if(ans[i]) {
            cnt.push_back(i - OFFSET);
        }
    }

    return cnt;
}

int main() {

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int x,y,z;
        fscanf(f,"%d %d %d",&x,&y,&z);
        if(z == 0) {
            graph[OFFSET - x].push_back(OFFSET + y);
            graph[OFFSET - y].push_back(OFFSET + x);
        }
        else if(z == 1) {
            graph[OFFSET - x].push_back(OFFSET - y);
        }
        else if(z == 2) {
            graph[OFFSET - y].push_back(OFFSET - x);
        }
        else {
            graph[OFFSET + x].push_back(OFFSET - y);
            graph[OFFSET + y].push_back(OFFSET - x);
        }
    }

    vector<int> tmp = solve_clauses();

    fprintf(g,"%d\n",(int)tmp.size());

    for(auto it:tmp) {
        fprintf(g,"%d\n",it);
    }

    return 0;
}
