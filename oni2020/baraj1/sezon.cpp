#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int LGMAX = 18;
const int NMAX = 100000;

int t;
int n;
pair<long long,int> v[NMAX + 5];
int aib[2 * NMAX + 5];
int l[NMAX + 5];
int r[NMAX + 5];
int lvl[NMAX + 5];
int lg2[2 * NMAX + 5];
int rmq[LGMAX + 1][2 * NMAX + 5];

int father[NMAX + 5];
bool is_unknown[NMAX + 5];
bool has_unknown_neighbor[NMAX + 5];

vector<int> graph[NMAX + 5];
int last_lin = 0;

void reset_aib(){
    for(int i = 1;i <= last_lin;i++){
        aib[i] = 0;
    }
}

void update(int pos,int val){
    for(;pos <= last_lin;pos += (-pos) & pos){
        aib[pos] += val;
    }
}

int query(int pos){
    int ans = 0;
    for(;pos;pos -= (-pos) & pos){
        ans += aib[pos];
    }
    return ans;
}

void dfs(int nod,int tata){
    father[nod] = tata;
    lvl[nod] = 1 + lvl[tata];
    last_lin++;
    rmq[0][last_lin] = nod;
    r[nod] = l[nod] = last_lin;

    for(auto it:graph[nod]){
        if(it == tata){
            continue;
        }
        dfs(it,nod);
        last_lin++;
        rmq[0][last_lin] = nod;
        r[nod] = last_lin;
    }
}

int best(int a,int b){
    return lvl[a] < lvl[b] ? a:b;
}

void make_rmq(){
    for(int h = 1;h <= LGMAX;h++){
        for(int i = 1;i <= last_lin;i++){
            rmq[h][i] = rmq[h - 1][i];
            if(i > (1 << (h - 1))){
                rmq[h][i] = best(rmq[h][i],rmq[h - 1][i - (1 << (h - 1))]);
            }
        }
    }
}

int lca(int u,int v){
    if(l[u] > l[v]){
        swap(u,v);
    }
    int h = lg2[l[v] - l[u] + 1];
    return best(rmq[h][l[v]],rmq[h][l[u] + (1 << h) - 1]);
}

int main(){

    lg2[1] = 0;

    for(int i = 2;i <= 2 * NMAX;i++){
        lg2[i] = 1 + lg2[i >> 1];
    }

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);

        for(int i = 1;i <= n;i++){
            scanf("%lld",&v[i].first);
            v[i].second = i;
            is_unknown[i] = false;
            graph[i].clear();
            has_unknown_neighbor[i] = false;
        }

        for(int i = 1;i < n;i++){
            int x,y;
            scanf("%d %d",&x,&y);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        sort(v + 1,v + 1 + n);
        reverse(v + 1,v + 1 + n);

        bool ok = true;

        for(int i = 1;i < n;i++){
            if(v[i].first == v[i + 1].first){
                ok = false;
            }
        }

        if(ok){
            last_lin = 0;
            dfs(1,0);
            make_rmq();
            reset_aib();
            for(int i = 1;i < n;i++){
                int nod = v[i].second;
                long long last = v[i].first;
                int it = v[i + 1].second;
                long long last_it = v[i + 1].first;

                int w = lca(nod,it);

                int dist = lvl[nod] + lvl[it] - 2 * lvl[w];
                int cnt_unknown = query(l[nod]) + query(l[it]) - 2 * query(l[w]) + is_unknown[w];

//                printf("deb %d %d %d %d %d %d %d\n",nod,it,w,last,last_it,dist,cnt_unknown);
//                printf("deb2 %d %d %d\n",lvl[nod],lvl[it],lvl[w]);

                if(last - last_it < dist || (dist & 1) != ((last - last_it) & 1) || cnt_unknown != dist - 1){
                    ok = false;
                    break;
                }else if(dist == 1 && has_unknown_neighbor[nod] == false && last - last_it != 1){
                    ok = false;
                    break;
                }
//                printf("deb3 update %d %d\n",l[nod],r[nod]);
                update(l[nod],1);
                update(r[nod] + 1,-1);
                is_unknown[nod] = true;
                for(auto it:graph[nod]){
                    has_unknown_neighbor[it] = true;
                }
            }
        }

        printf("%d",ok);
    }

    return 0;
}
