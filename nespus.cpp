#include <cstdio>
#include <deque>
#include <queue>
#include <vector>

using namespace std;

FILE *f = fopen("nespus.in","r");
FILE *g = fopen("nespus.out","w");

struct edge_t{
    int u,v;
    int cost;

    edge_t(){
        u = 0;
        v = 0;
        cost = 0;
    }

    edge_t(int u,int v,int cost){
        this->u = u;
        this->v = v;
        this->cost = cost;
    }

    bool operator < (const edge_t &other)const{
        if(cost != other.cost){
            return cost < other.cost;
        }

        if(u != other.u){
            return u < other.u;
        }

        return v < other.v;
    }
};

void link(edge_t e);///it's not what you think i swear
void cut(edge_t e);
int weight(int u);

const int NMAX = 1e5;

int n,k;

///proper weight calculation
vector<int> liniarizare(1,0);
int aib[2 * NMAX + 5];
int first_pos[NMAX + 5];
int last_pos[NMAX + 5];
int W[4 * NMAX + 5];

///coloring
int color[NMAX + 5];
int root[4 * NMAX + 5];///root[color] = the root of all verticies colored with color
int last_color = 0;
int father[NMAX + 5];

///i don't know how to call it really
vector<edge_t> events;
deque<edge_t> graph[NMAX + 5];

///initial dfs, makes liniarizare and father ,colors and root
void dfs(int nod,int tata){
    father[nod] = tata;
    color[nod] = ++last_color;
    root[last_color] = nod;
	W[last_color] = 1;

    first_pos[nod] = liniarizare.size();
    liniarizare.push_back(nod);

    for(auto it:graph[nod]){
        int to = nod ^ it.u ^ it.v;
        if(to != tata){
            dfs(to,nod);
        }
    }

    last_pos[nod] = liniarizare.size();
    liniarizare.push_back(nod);
}

///weight calculation implementation

void aib_update(int pos,int val){
    for(;pos < (int)liniarizare.size();pos += (-pos)&pos){
        aib[pos] += val;
    }
}

int aib_query(int pos){
    int sum = 0;
    for(;pos;pos -= (-pos) & pos){
        sum += aib[pos];
    }
    return sum;
}

///the weight of u,not of his component
int weight(int u){
    return aib_query(first_pos[u]) - aib_query(last_pos[u]);
}

///u is ancestors of v
void add_weight_from_u_to_v(int u,int v,int w){
    aib_update(first_pos[u],w);
    aib_update(first_pos[v],-w);
}

///coloring implementation

int recolor(int nod,int old_color,int new_color){
    queue<int> nodes;
    nodes.push(nod);
    color[nod] = new_color;
	int num = 0;

    while(!nodes.empty()){
		num++;
        int nod = nodes.front();nodes.pop();
        for(auto it:graph[nod]){
            int to = it.u ^ it.v ^ nod;
            if(color[to] == old_color){
                color[to] = new_color;
                nodes.push(to);
            }
        }
    }
	return num;
}

///v is a son of u
void link(edge_t e){

    int u = e.u,v = e.v;

    if(father[v] != u){
        swap(u,v);
    }

    int wv = W[color[v]];
    int wu = W[color[u]];

    if(wv < wu){
		W[color[u]] += wv;
		W[color[v]] = 0;
        recolor(v,color[v],color[u]);
    }

    else{
		W[color[v]] += wu;
		W[color[u]] = 0;
        root[color[v]] = root[color[u]];
        recolor(u,color[u],color[v]);
    }

    graph[e.u].push_back(e);
    graph[e.v].push_back(e);
    add_weight_from_u_to_v(root[color[v]],v,wv);
}

///v is a son of u
void cut(edge_t e){
    int u = e.u,v = e.v;

    if(father[v] != u){
        swap(u,v);
    }

    int wv = weight(v);
    int wu = W[color[u]];

    graph[u].pop_front();
    graph[v].pop_front();

    if(wv < wu - wv){
        root[++last_color] = v;
        W[last_color] = recolor(v,color[u],last_color);
		W[color[u]] -= W[last_color];
    }

    else{
        root[++last_color] = root[color[u]];
        root[color[v]] = v;
        W[last_color] = recolor(u,color[u],last_color);
		W[color[v]] -= W[last_color];
    }

    add_weight_from_u_to_v(root[color[u]],v,-wv);
 }

const int LEN = 1e4;
int ind = LEN - 1;
char buff[LEN];

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9'){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    return ans;
}

int main(){
    n = i32();
    k = i32();

    for(int i = 1;i < n;i++){
        int u,v,cost;
        u = i32();
        v = i32();
        cost = i32();
        events.push_back(edge_t(u,v,cost));
        graph[u].push_back(edge_t(u,v,cost));
        graph[v].push_back(edge_t(u,v,cost));
    }

    dfs(1,0);

    for(int i = 1;i <= n;i++){
        graph[i].clear();
        aib_update(first_pos[i],1);
        if(first_pos[i] + 1 < (int)liniarizare.size()){
            aib_update(first_pos[i] + 1,-1);
        }
    }

    vector<int> nodes_bigger_than_k;
    int j = -1;

    int ans = 1LL << 30;

    for(int i = 0;i < (int)events.size();i++){
        while(!nodes_bigger_than_k.empty() && W[color[nodes_bigger_than_k.back()]] < k){
            nodes_bigger_than_k.pop_back();
        }

        if(!nodes_bigger_than_k.empty()){
            ans = min(ans,events[j].cost - events[i].cost);
        }

        else{
            while(j < (int)events.size() - 1 && nodes_bigger_than_k.empty()){
                j++;
                link(events[j]);
                if(W[color[events[j].u]] >= k){
                    nodes_bigger_than_k.push_back(events[j].u);
                    nodes_bigger_than_k.push_back(events[j].v);
                }
            }

            if(nodes_bigger_than_k.empty()){
                goto done1;
            }
            else{
                ans = min(ans,events[j].cost - events[i].cost);
            }
        }

        cut(events[i]);
	    nodes_bigger_than_k.push_back(events[i].v);
	    nodes_bigger_than_k.push_back(events[i].u);
    }

    done1:;
    fprintf(g,"%d",ans);

    return 0;
}
