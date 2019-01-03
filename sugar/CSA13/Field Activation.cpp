#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 300;
const int QMAX = 1e5;
const int LGMAX = 8;
const int MAX_NODES_WITHOUT_VIRTUAL = 8 * (NMAX + 1) * (NMAX + 1) * (LGMAX + 1) + 2 * (NMAX + 1) * (LGMAX + 1) + 2 * (NMAX + 1) + 2;
const int MAX_NODES_WITH_VIRTUAL = MAX_NODES_WITHOUT_VIRTUAL + QMAX;

int lg2[NMAX + 5];

int n,m,q;
vector<int> graph[MAX_NODES_WITH_VIRTUAL + 5];

int last_virtual = MAX_NODES_WITHOUT_VIRTUAL + 2;

bool drawn[MAX_NODES_WITHOUT_VIRTUAL + 2];
vector<int> active_nodes;

inline int get_virtual_node() {
    return ++last_virtual;
}

inline int get_RMQ_node(int aint_node, int x, int y, int prop_dir) {
    return (aint_node) * (NMAX + 1) * (LGMAX + 1) * 2 + (y) * (LGMAX + 1) * 2 + (x) * 2 + prop_dir;
}

vector< pair<int,int> > edges;

inline void add_edge(int x, int y, bool dir) {
    if(dir) {
        swap(x,y);
    }
    graph[x].push_back(y);
    edges.push_back({x,y});
}

inline void init_RMQ() {
    lg2[0] = -1;
    for(int i = 1; i <= NMAX; i++) {
        lg2[i] = 1+ lg2[i / 2];
    }
}

struct state_t {
    int node;
    int x;
    int y;
    int dir;
    int st;
    int dr;

    inline int get_node() {
        return get_RMQ_node(node,x,y,dir);
    }
};

void draw_RMQ(int aint_node, int x, int y,int prop_dir,int st,int dr) {
    vector<state_t> v(1, {aint_node,x,y,prop_dir,st,dr});

    for(int i = 0; i < (int)v.size(); i++) {
        if(drawn[v[i].get_node()]) {
            continue;
        }

        drawn[v[i].get_node()] = true;

        if(v[i].st == v[i].dr) {
            if(v[i].x == 0) {
                continue;
            }
            state_t st = v[i];
            state_t dr = v[i];
            st.x--;
            dr.x--;
            dr.y -= (1 << (dr.x));
            add_edge(v[i].get_node(),st.get_node(),prop_dir);
            v.push_back(st);

            if(dr.y > 0) {
                add_edge(v[i].get_node(),dr.get_node(),prop_dir);
                v.push_back(dr);
            }
        }
        else {
            state_t st = v[i];
            state_t dr = v[i];
            st.node = st.node * 2;
            dr.node = dr.node * 2 + 1;
            st.dr = (st.st + st.dr) / 2;
            dr.st = (dr.st + dr.dr) / 2 + 1;
            add_edge(v[i].get_node(),st.get_node(),prop_dir);
            add_edge(v[i].get_node(),dr.get_node(),prop_dir);
            v.push_back(st);
            v.push_back(dr);
        }
    }
}

void query(int node,int st,int dr,int S,int D,int xx,int y1,int y2,int pivot,int dir) {
    if(dr < S || D < st) {
        return ;
    }

    if(S <= st && dr <= D) {
        draw_RMQ(node,xx,y1,!dir,st,dr);
        draw_RMQ(node,xx,y2,!dir,st,dr);
        add_edge(get_RMQ_node(node,xx,y1,!dir),pivot,dir);
        add_edge(get_RMQ_node(node,xx,y2,!dir),pivot,dir);
        return ;
    }

    int mid = (st + dr) / 2;
    query(node * 2,st,mid,S,D,xx,y1,y2,pivot,dir);
    query(node * 2 + 1,mid + 1,dr,S,D,xx,y1,y2,pivot,dir);
}

void draw(int l11,int c11,int l12,int c12,int l21,int c21,int l22,int c22) {
    int pivot = get_virtual_node();
    active_nodes.push_back(pivot);
    query(1,1,n,l11,l12,lg2[c12 - c11 + 1],c11 + (1 << lg2[c12 - c11 + 1]) - 1,c12,pivot,0);
    query(1,1,n,l21,l22,lg2[c22 - c21 + 1],c21 + (1 << lg2[c22 - c21 + 1]) - 1,c22,pivot,1);
}

void add_remaining_nodes(int nod,int st,int dr,vector<int> &active) {
    if(st == dr) {
        for(int i = 1; i <= m; i++) {
            active.push_back(get_RMQ_node(nod,0,i,0));
            active.push_back(get_RMQ_node(nod,0,i,1));
            add_edge(get_RMQ_node(nod,0,i,0),get_RMQ_node(nod,0,i,1),0);
            add_edge(get_RMQ_node(nod,0,i,0),get_RMQ_node(nod,0,i,1),1);
        }
        return ;
    }

    int mid = (st + dr) / 2;

    add_remaining_nodes(nod * 2,st,mid,active);
    add_remaining_nodes(nod * 2 + 1,mid + 1,dr,active);
}

int ctc_remap[MAX_NODES_WITH_VIRTUAL + 5];
bool viz[MAX_NODES_WITH_VIRTUAL + 5];
int low[MAX_NODES_WITH_VIRTUAL + 5];
int id[MAX_NODES_WITH_VIRTUAL + 5],last_id;
int st[MAX_NODES_WITH_VIRTUAL + 5],len;
bool inst[MAX_NODES_WITH_VIRTUAL + 5];
int last_ctc_id = 0;
int ctc_gr[MAX_NODES_WITH_VIRTUAL + 5];


void ctc(int nod) {
    low[nod] = id[nod] = ++last_id;
    viz[nod] = 1;
    st[++len] = nod;
    inst[st[len]] = true;

    for(auto it:graph[nod]) {
        if(!viz[it]) {
            ctc(it);
        }

        if(inst[it]) {
            low[nod] = min(low[nod],low[it]);
        }
    }

    if(low[nod] == id[nod]) {
        last_ctc_id++;
        while(st[len] != nod) {
            ctc_remap[st[len]] = last_ctc_id;
            inst[st[len]] = false;
            len--;
        }
        ctc_remap[st[len]] = last_ctc_id;
        inst[st[len]] = false;
        len--;
    }
}

int main() {

    init_RMQ();
    scanf("%d %d %d\n",&n,&m,&q);

    while(q--) {
        int l11,c11,l12,c12,l21,c21,l22,c22;
        scanf("%d %d %d %d %d %d %d %d\n",&l11,&c11,&l12,&c12,&l21,&c21,&l22,&c22);
        l11++;
        c11++;
        l12++;
        c12++;
        l21++;
        c21++;
        l22++;
        c22++;
        draw(l11,c11,l12,c12,l21,c21,l22,c22);
    }

    for(int i = 0; i <= MAX_NODES_WITHOUT_VIRTUAL; i++) {
        if(drawn[i]) {
            active_nodes.push_back(i);
        }
    }

    add_remaining_nodes(1,1,n,active_nodes);

    for(auto it:active_nodes) {
        if(!viz[it]) {
            ctc(it);
        }
    }


    for(auto it:edges) {
        if(ctc_remap[it.first] == ctc_remap[it.second]) {
            continue;
        }
        ctc_gr[ctc_remap[it.second]]++;
    }

    int ans = 0;

    for(int i = 1; i <= last_ctc_id; i++) {
        if(ctc_gr[i] == 0) {
            ans++;
        }
    }

    printf("%d\n",ans);

    return 0;
}
