#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

FILE *f = fopen("traffickers.in","r");
FILE *g = fopen("traffickers.out","w");

const int LGMAX = 14;
const int NMAX = 3e4;

vector<int> graph[NMAX + 5];

struct state_t{
	int v[215];
	
	state_t(){
		memset(v,0,sizeof(v));
	}
	
	inline int coord_to_pos(int x,int y){
		return x * (x - 1) / 2 + y;
	}
	
	inline int get(int x,int y){
		return v[coord_to_pos(x,y)];
	}
	
	inline void modif(int x,int y,int val){
		v[coord_to_pos(x,y)] += val;
	}
	
	inline void overwr(int x,int y,int val){
		v[coord_to_pos(x,y)] = val;
	}
	
	state_t operator + (const state_t &other)const{
		state_t ans;
		for(int i = 0;i < 215;i++){
			ans.v[i] = this->v[i] + other.v[i];
		}
		return ans;
	}
};

int liniarizare[2 * NMAX + 5];
int lin_sz;
int fst[NMAX + 5];
int lst[NMAX + 5];
int lvl[NMAX + 5];
int T[LGMAX + 1][NMAX + 5];
int n;

void dfs(int nod,int tata){
	lvl[nod] = 1 + lvl[tata];
	T[0][nod] = tata;
	liniarizare[++lin_sz] = nod;fst[nod] = lin_sz;

	for(auto it:graph[nod]){
		if(it != tata){
			dfs(it,nod);
		}
	}
	
	liniarizare[++lin_sz] = nod;lst[nod] = lin_sz;
}

void prelca(){
	for(int i = 1;i <= LGMAX;i++){
		for(int j = 1;j <= n;j++){
			T[i][j] = T[i - 1][T[i - 1][j]];
		}
	}
}

int lca(int x,int y){
	
	if(lvl[x] > lvl[y]){
		swap(x,y);
	}
	
	int dist = lvl[y] - lvl[x];
	
	for(int i = LGMAX;i >= 0;i--){
		if((dist >> i)){
			y = T[i][y];
			dist ^= (1 << i);
		}
	}
	
	if(x == y){
		return x;
	}
	
	for(int i = LGMAX;i >= 0;i--){
		if(T[i][x] != T[i][y]){
			y = T[i][y];
			x = T[i][x];
		}
	}
	return T[0][x];
}

state_t aib[2 * NMAX + 5];

void up_aib(int pos,int x,int y,int val){
	for(;pos <= lin_sz;pos += (-pos) & pos){
		aib[pos].modif(x,y,val);
	}
}

state_t query_aib(int pos){
	state_t ans;
	for(;pos;pos -= (-pos) & pos){
		ans = ans + aib[pos];
	}
	return ans;
}

void update(int x,int y,int sgn){
	int z = lca(x,y);
	int dist = lvl[x] + lvl[y] - 2 * lvl[z] + 1;
	// fprintf(stdout,"%d %d %d %d %d\n",x,y,z,sgn,dist);
	for(int nod = x,r = 0;nod != z;nod = T[0][nod],r++){
		up_aib(fst[nod],dist,r,sgn);
		up_aib(lst[nod],dist,r,-sgn);
	}
	
	for(int nod = y,r = dist - 1;nod != z;nod = T[0][nod],r--){
		up_aib(fst[nod],dist,r,sgn);
		up_aib(lst[nod],dist,r,-sgn);
	}
	
	up_aib(fst[z],dist,lvl[x] - lvl[z],sgn);
	up_aib(lst[z],dist,lvl[x] - lvl[z],-sgn);
}

int chestie(int c,int r,int x,int y){
	x += 2 * c;
	y += 2 * c;
	x -= r;
	y -= r;
	return y / c - (x - 1) / c;
}

long long query(int x,int y,int t1,int t2){
	state_t meanwhile;
	for(int c = 1;c <= 20;c++){
		for(int r = 0;r < c;r++){
			meanwhile.overwr(c,r,chestie(c,r,t1,t2));
			// fprintf(stdout,"%d ",chestie(c,r,t1,t2));
		}
		// fprintf(stdout,"\n");
	}
	
	int z = lca(x,y);
	
	// fprintf(stdout,"%d %d %d\n",x,y,z);
	state_t u = query_aib(fst[x]);
	state_t v = query_aib(fst[y]);
	state_t com1 = query_aib(fst[z]);
	state_t com2 = query_aib(fst[T[0][z]]);
	long long ans = 0;
	
	for(int c = 1;c <= 20;c++){
		for(int r = 0;r < c;r++){
			int val = u.get(c,r) + v.get(c,r) - com1.get(c,r) - com2.get(c,r);
			ans += 1LL * val * meanwhile.get(c,r);
		}
	}
	return ans;
}

int main(){
	
	fscanf(f,"%d",&n);
	
	for(int i = 1;i < n;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	dfs(1,0);
	prelca();
	
	int k;
	
	fscanf(f,"%d",&k);
	
	for(int i = 1;i <= k;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		update(x,y,1);
	}
	
	int q;
	
	fscanf(f,"%d",&q);
	
	while(q--){
		int op,x,y,t1,t2;
		fscanf(f,"%d %d %d",&op,&x,&y);
		if(op == 1){
			update(x,y,1);
		}
		else if(op == 2){
			update(x,y,-1);
		}
		else{
			fscanf(f,"%d %d",&t1,&t2);
			fprintf(g,"%lld\n",query(x,y,t1,t2));
		}
		
	}
	
	return 0;
}
