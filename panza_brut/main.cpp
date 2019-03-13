#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("panza.in","r");
FILE *g = fopen("panza.ok","w");

const int NMAX = 1e5;
const int MMAX = 1e5;
const long long inf = 2e12;

int n,m,st,dr;
int a[MMAX + 5];

int x[NMAX + 5];
int y[NMAX + 5];

vector< vector<long long> > dist[2];

struct state_t{
    long long cost;
    int x;
    int y;
    int tp;
    bool operator < (const state_t &other)const{
        return this->cost > other.cost;
    }
};

priority_queue<state_t> pq;

int main(){

    fscanf(f,"%d %d %d %d",&n,&m,&st,&dr);

    for(int i = 1;i <= m;i++){
        fscanf(f,"%d",&a[i]);
    }

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d %d",&x[i],&y[i]);
    }

    dist[0] = vector<vector<long long> > (n + 1,vector<long long>(m + 1,inf));
    dist[1] = vector<vector<long long> > (n + 1,vector<long long>(m + 1,inf));

    dist[x[1] <= st && st <= y[1]][1][st] = 0;
    pq.push({0,1,st,x[1] <= st && st <= y[1]});

    while(!pq.empty()){
        state_t tmp = pq.top();
        pq.pop();
        long long cost = tmp.cost;
        int i = tmp.x;
        int j = tmp.y;
        int tp = tmp.tp;

        if(cost != dist[tp][i][j]){
            continue;
        }

        if(tp == 0){
            if(j > 1){
                state_t to;
                to.cost = cost + 1;
                to.y = j - 1;
                to.x = i;
                to.tp = (x[i] <= to.y && to.y <= y[i]);
                if(dist[to.tp][to.x][to.y] > to.cost){
                    dist[to.tp][to.x][to.y] = to.cost;
                    pq.push(to);
                }
            }
            if(j < m){
                state_t to;
                to.cost = cost + 1;
                to.y = j + 1;
                to.x = i;
                to.tp = (x[i] <= to.y && to.y <= y[i]);
                if(dist[to.tp][to.x][to.y] > to.cost){
                    dist[to.tp][to.x][to.y] = to.cost;
                    pq.push(to);
                }
            }
        }
        else{
            if(j > 1){
                state_t to;
                to.cost = cost + 1;
                to.y = j - 1;
                to.x = i;
                to.tp = 1;
                if(dist[to.tp][to.x][to.y] > to.cost){
                    dist[to.tp][to.x][to.y] = to.cost;
                    pq.push(to);
                }
            }
            if(j < m){
                state_t to;
                to.cost = cost + 1;
                to.y = j + 1;
                to.x = i;
                to.tp = 1;
                if(dist[to.tp][to.x][to.y] > to.cost){
                    dist[to.tp][to.x][to.y] = to.cost;
                    pq.push(to);
                }
            }
            if(i < n){
                state_t to;
                to.cost = cost + a[j];
                to.x = i + 1;
                to.y = j;
                to.tp = (x[to.x] <= to.y && to.y <= y[to.x]);
                if(dist[to.tp][to.x][to.y] > to.cost){
                    dist[to.tp][to.x][to.y] = to.cost;
                    pq.push(to);
                }
            }
        }
    }

    fprintf(g,"%lld",dist[1][n][dr]);

    fclose(f);
    fclose(g);

    return 0;
}
