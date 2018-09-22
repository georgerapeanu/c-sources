#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
   
using namespace std;
   
FILE *f = fopen("flareon.in","r");
FILE *g = fopen("flareon.out","w");
   
const int NMAX = 2e5;
const int MMAX = 5e5;
   
int n,m;
vector<int> graph[NMAX + 5];
vector<int> pokemons[NMAX + 5];
bool viz[NMAX + 5];
int weight[NMAX + 5];
long long dmg[NMAX + 5];
   
void recalc_weights(int nod,int tata){
    weight[nod] = 1;
    for(auto it:graph[nod]){
        if(it != tata && !viz[it]){
            recalc_weights(it,nod);
            weight[nod] += weight[it];
        }
    }
}
   
vector<int> bfs;
vector<int> dist(NMAX + 5);
vector<int> flareons;
int maxdist;
   
void get_stuff(int nod,bool do_bfs,bool do_flareons){
   
    if(do_bfs){
        for(auto it:bfs){
            dist[it] = 0;
        }
        bfs.clear();
        maxdist = 0;
    }
   
    if(do_flareons){
        flareons.clear();
    }
   
    queue< pair<pair<int,int>,int> > Q;
    Q.push(make_pair(make_pair(nod,0),0));
   
    while(!Q.empty()){
        int nod = Q.front().first.first;
        int tata = Q.front().first.second;
        int penal = Q.front().second;///variabila descrie intr-un mod indirect atat cititorul cat si cel care a scris sursa
        Q.pop();
   
   
        if(do_bfs){
            bfs.push_back(nod);
            dist[nod] = penal;
            maxdist = max(maxdist,penal);
        }
        if(do_flareons){
            for(auto it:pokemons[nod]){
                if(it - penal > 0){
                    flareons.push_back(it - penal);
                }
            }
        }
   
        for(auto it:graph[nod]){
            if(it != tata && !viz[it]){
                Q.push(make_pair(make_pair(it,nod),penal + 1));
            }
        }
    }
}
   
vector<long long> a_coef(NMAX + 5);
vector<long long> b_coef(NMAX + 5);
   
void baga(int a,int b,int l,int r){
    b_coef[l] += b;
    b_coef[r + 1] -= b;
    a_coef[l] += a;
    a_coef[r + 1] -= a;
    b_coef[l] -= 1LL * a * l;
    b_coef[r + 1] += 1LL * a * l;
}
   
void process(int nod){
    for(int i = 0;i <= maxdist + 1;i++){
        a_coef[i] = b_coef[i] = 0;
    }
    get_stuff(nod,1,1);
    for(auto it:flareons){
        baga(-1,it,0,min(maxdist,it - 1));
    }
   
    for(int i = 1;i <= maxdist;i++){
        a_coef[i] += a_coef[i - 1];
        b_coef[i] += b_coef[i - 1];
    }
   
    for(auto it:bfs){
        dmg[it] += (a_coef[dist[it]] * dist[it] + b_coef[dist[it]]);
    }
   
    for(auto it:graph[nod]){
        if(!viz[it]){
            for(int i = 0;i <= maxdist + 1;i++){
                a_coef[i] = b_coef[i] = 0;
            }
            get_stuff(it,1,1);
            for(auto &it:flareons){
                it -= 2;
                if(it <= 0){
                    continue;
                }
                baga(-1,it,0,min(maxdist,it - 1));
            }
   
            for(int i = 1;i <= maxdist;i++){
                a_coef[i] += a_coef[i - 1];
                b_coef[i] += b_coef[i - 1];
            }
   
            for(auto it:bfs){
                dmg[it] -= (a_coef[dist[it]] * dist[it] + b_coef[dist[it]]);
            }
        }
    }
}
   
void solve(int nod){
    recalc_weights(nod,0);
   
    int tata = 0;
    int centroid = nod;
   
    while(1){
        int child = -1;
        for(auto it:graph[centroid]){
            if(!viz[it] && tata != it && 2 * weight[it] > weight[nod]){
                child = it;
                break;
            }
        }
   
        if(child != -1){
            tata = centroid;
            centroid = child;
            continue;
        }
        break;
    }
   
    viz[centroid] = 1;
    for(auto it:graph[centroid]){
        if(!viz[it]){
            solve(it);
        }
    }
   
   process(centroid);
   
    viz[centroid] = 0;
}
   
const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
	int ans = 0;
	while(buff[ind] < '0' || buff[ind] > '9'){
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	
	while(buff[ind] >= '0' && buff[ind] <= '9'){
		ans = ans * 10 + (buff[ind] - '0');
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	
	return ans;
}
   
int main(){
   
    n = i32();m = i32();
      
    for(int i = 2;i <= n;i++){
        int x;
        x = i32();
        graph[x].push_back(i);
        graph[i].push_back(x);
    }
	   
    for(int i = 1;i <= m;i++){
        int x,p;
        x = i32();p = i32();
        pokemons[x].push_back(p);
    }
   
    solve(1);
   
    for(int i = 1;i <= n;i++){
        fprintf(g,"%lld\n",dmg[i]);
    }
   
    fclose(f);
    fclose(g);
   
    return 0;
}