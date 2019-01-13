#define JUDGE
#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("snake.in","r");
FILE *g = fopen("snake.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int NMAX = 100;

struct state_t {
    int x,y;
};
state_t pos[NMAX * NMAX + 5];

int v[NMAX + 5][NMAX + 5];
int n,m,l;

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

///1-indexed
class BipartiteMatcher {
public:

    vector<int> L,R;
    vector< vector<int> > graph;

private:

    vector<bool> viz;
    bool pair_up(int nod) {
        if(viz[nod]) {
            return 0;
        }
        viz[nod] = 1;

        for(auto it:graph[nod]) {
            if(!R[it]) {
                R[it] = nod;
                L[nod] = it;
                return 1;
            }
        }

        for(auto it:graph[nod]) {
            if(pair_up(R[it])) {
                R[it] = nod;
                L[nod] = it;
                return 1;
            }
        }
        return 0;
    }

public:

    BipartiteMatcher(int n,int m) {
        graph.resize(n + 1);
        L.resize(n + 1);
        R.resize(m + 1);
        viz.resize(n + 1);
    }

    void add_edge(int u,int v) {
        graph[u].push_back(v);
    }

    void reset_match() {
        fill(L.begin(),L.end(),0);
        fill(R.begin(),R.end(),0);
        fill(viz.begin(),viz.end(),0);
    }

    void reset_full() {
        fill(L.begin(),L.end(),0);
        fill(R.begin(),R.end(),0);
        fill(viz.begin(),viz.end(),0);
        fill(graph.begin(),graph.end(),vector<int>());
    }

    int max_match() {
        int ans = 0;
        bool ok = 1;
        while(ok) {
            ok = 0;
            fill(viz.begin(),viz.end(),0);
            for(int i = 1; i < (int)L.size(); i++) {
                if(!L[i] && pair_up(i)) {
                    ans++;
                    ok = 1;
                }
            }
        }
        return ans;
    }
};

inline int coord_to_id(int x,int y) {
    return (x - 1) * m + y;
}

inline pair<int,int> id_to_coord(int id) {
    int x = (id - 1) / m + 1;
    int y = id - (x - 1) * m;

    return {x,y};
}

int main() {

    fscanf(f,"%d %d %d",&n,&m,&l);

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            fscanf(f,"%d",&v[i][j]);
            if(v[i][j] > 0) {
                pos[v[i][j]] = {i,j};
            }
        }
    }

    for(int i = 1; i < l; i += 2) {
        if(pos[i].x == pos[i + 2].x) {
            v[pos[i].x][(pos[i].y + pos[i + 2].y) / 2] = i + 1;
            pos[i + 1] = {pos[i].x,(pos[i].y + pos[i + 2].y) / 2};
        }

        else if(pos[i].y == pos[i + 2].y) {
            v[(pos[i].x + pos[i + 2].x) / 2][pos[i].y] = i + 1;
            pos[i + 1] = {(pos[i].x + pos[i + 2].x) / 2,pos[i].y};
        }
    }

    /* for(int i = 1;i <= n;i++){
         for(int j = 1;j <= m;j++){
             printf("%d ",v[i][j]);
         }
         printf("\n");
     }*/

    BipartiteMatcher solve(l / 2,n * m);

    for(int i = 1; i < l; i++) {
        if(pos[i + 1].x != 0) {
            continue;
        }

        int ind = 0;

        if(pos[i + 2].x == pos[i].x - 1) {
            if(pos[i + 2].y == pos[i].y - 1) {
                ind = 3;
            }
            else {
                ind = 0;
            }
        }
        else {
            if(pos[i + 2].y == pos[i].y - 1) {
                ind = 2;
            }
            else {
                ind = 1;
            }
        }

        // printf("%d %d\n",i + 1,ind);

        int x = pos[i].x;
        int y = pos[i].y;
        int xx1 = x + dx[ind],yy1 = y + dy[ind];
        int xx2 = x + dx[(ind + 1) % 4],yy2 = y + dy[(ind + 1) % 4];
        if(v[xx1][yy1] == 0)solve.add_edge((i + 1) / 2,coord_to_id(xx1,yy1));
        if(v[xx2][yy2] == 0)solve.add_edge((i + 1) / 2,coord_to_id(xx2,yy2));
    }

    solve.max_match();

    for(int i = 1; i <= l / 2; i++) {
        if(solve.L[i]) {
            pair<int,int> tmp = id_to_coord(solve.L[i]);
            v[tmp.first][tmp.second] = 2 * i;
        }
    }

    /*for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            printf("%d ",v[i][j]);
        }
        printf("\n");
    }*/
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            fprintf(g,"%d ",v[i][j]);
        }
        fprintf(g,"\n");
    }
    return 0;
}
