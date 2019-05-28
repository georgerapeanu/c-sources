#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <cassert>

using namespace std;

const int NMAX = 15e4;
const int QMAX = 15e4;
const int SIGMA = 30;

struct data_t {
    int fr[SIGMA + 5];
    int wildcards;

    data_t() {
        memset(fr,0,sizeof(fr));
        wildcards = 0;
    }

    void change_char(char a,int delta) {
        if(a == '?') {
            wildcards += delta;
        }
        else {
            fr[a - 'a' + 1] += delta;
        }
    }

    data_t operator + (const data_t &other)const {
        data_t a = *this;
        data_t b = other;

        for(int i = 1; i <= SIGMA; i++) {
            if(a.fr[i] > b.fr[i]) {
                b.wildcards -= (a.fr[i] - b.fr[i]);
            }
            else if(a.fr[i] < b.fr[i]) {
                a.wildcards -= (b.fr[i] - a.fr[i]);
                a.fr[i] = b.fr[i];
            }
        }

        return a;
    }

    void normal_add(const data_t &other) {
        this->wildcards += other.wildcards;
        for(int i = 1; i <= SIGMA; i++) {
            this->fr[i] += other.fr[i];
        }
    }
};

int n,q;
int father[NMAX + 5];
bool is_bad[NMAX + 5];
char father_char[NMAX + 5];
vector<int> graph[NMAX + 5];
vector<int> comp_graph[NMAX + 5];

data_t stuff[NMAX + 5];
data_t upward[NMAX + 5];

int leaf_level = -1;
int lvl[NMAX + 5];
int target_edge[NMAX + 5];

int dfs(int nod) {
    lvl[nod] = 1 + lvl[father[nod]];

    if((int)graph[nod].size() == 2) {
        int a = dfs(graph[nod][0]);
        int b = dfs(graph[nod][1]);
        father[a] = nod;
        father[b] = nod;
        comp_graph[nod].push_back(a);
        comp_graph[nod].push_back(b);
        stuff[nod] = stuff[a] + stuff[b];
        is_bad[nod] = (is_bad[a] | is_bad[b] | (stuff[nod].wildcards < 0));
        if(father_char[nod]) {
            upward[nod].change_char(father_char[nod],1);
        }
        stuff[nod].normal_add(upward[nod]);
        target_edge[nod] = nod;
        return nod;
    }

    if((int)graph[nod].size() == 1) {
        int u;
        data_t tmp;
        for(u = nod; (int)graph[u].size() == 1; u = graph[u][0]) {
            lvl[u] = 1 + lvl[father[u]];
            if(father_char[u]) {
                tmp.change_char(father_char[u],1);
            }
        }

        dfs(u);
        upward[u].normal_add(tmp);
        stuff[u].normal_add(tmp);

        int tmp_u = u;

        for(u = nod; (int)graph[u].size() == 1; u = graph[u][0]) {
            target_edge[u] = tmp_u;
        }

        if(nod == 1) {
            target_edge[1] = 1;
            father[u] = 1;
            comp_graph[1].push_back(u);
            stuff[1] = stuff[u];
            is_bad[1] = (is_bad[u] | (stuff[1].wildcards < 0));
            return 1;
        }
        return u;
    }

    if((int)graph[nod].size() == 0) {
        target_edge[nod] = nod;
        if(leaf_level == -1) {
            leaf_level = lvl[nod];
        }

        if(leaf_level != lvl[nod]) {
            for(int i = 1; i <= q; i++) {
                printf("Fou\n");
            }
            exit(0);
        }

        if(father_char[nod]) {
            upward[nod].change_char(father_char[nod],1);
        }
        is_bad[nod] = false;
        stuff[nod] = upward[nod];
        return nod;
    }
}

void print_comp(int nod) {
    printf("%d %d ",nod,father[nod]);
    printf("%d ",stuff[nod].wildcards);
    for(int i = 1; i <= SIGMA; i++) {
        printf("%d ",stuff[nod].fr[i]);
    }
    printf("sons ");

    for(auto it:comp_graph[nod]) {
        printf("%d ",it);
    }

    printf("upward stuff ");
    printf("%d ",upward[nod].wildcards);
    for(int i = 1; i <= SIGMA; i++) {
        printf("%d ",upward[nod].fr[i]);
    }

    printf("\n");

    for(auto it:comp_graph[nod]) {
        print_comp(it);
    }
}

///God help all of this code and all the ones that will come after

void update(int v,char c) {
    char rem_ch = father_char[v];
    char add_ch = c;
    father_char[v] = c;
    v = target_edge[v];
    upward[v].change_char(rem_ch,-1);
    upward[v].change_char(add_ch,1);
    for(int nod = v; nod; nod = father[nod]) {
        stuff[nod] = data_t();
        is_bad[nod] = false;
        if((int)graph[nod].size() > 0) {
            stuff[nod] = stuff[comp_graph[nod][0]];
            is_bad[nod] = (is_bad[comp_graph[nod][0]] | (stuff[nod].wildcards < 0));
        }
        if((int)graph[nod].size() > 1) {
            stuff[nod] = stuff[comp_graph[nod][0]] + stuff[comp_graph[nod][1]];
            is_bad[nod] = ((is_bad[comp_graph[nod][0]]) | (is_bad[comp_graph[nod][1]]) | (stuff[nod].wildcards < 0));
        }
        stuff[nod].normal_add(upward[nod]);
    }
    if(is_bad[1] == false) {
        printf("Shi ");
        int ans = 0;
        for(int i = 1; i <= 'z' - 'a' + 1; i++) {
            ans += i * (stuff[1].wildcards + stuff[1].fr[i]);
        }
        printf("%d\n",ans);
    }
    else {
        printf("Fou\n");
    }
    //  print_comp(1);
}

int status_dfs(int nod) {
    int lg = 0;

    for(auto it:comp_graph[nod]) {
        lg = max(lg,status_dfs(it));
    }
    return 1 + lg;
}

int main() {

    scanf("%d %d\n",&n,&q);

    for(int i = 2; i <= n; i++) {
        scanf("%d %c\n",&father[i],&father_char[i]);
        graph[father[i]].push_back(i);
    }

    dfs(1);
    while(q--) {
        int v;
        char c;
        scanf("%d %c\n",&v,&c);
        update(v,c);
    }

    fprintf(stderr,"%d\n",status_dfs(1));

    return 0;
}
