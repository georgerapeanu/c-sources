#include <cstdio>
#include <algorithm>
#include <vector>
#include <stdexcept>

using namespace std;

FILE *f = fopen("rafaela.in","r");
FILE *g = fopen("rafaela.out","w");

///0-indexed;
class SegmentTree{
private:

	bool enforce_throws;
	int n;
	vector<int> aint;
	vector<int> lazy;
	
	void build(int nod,int st,int dr,vector<int> &base){
		lazy[nod] = 0;
		aint[nod] = 0;
		
		if(st == dr){
			aint[nod] = base[st];
			return;
		}
		
		int mid = (st + dr) / 2;
		
		build(nod * 2,st,mid,base);
		build(nod * 2 + 1,mid + 1,dr,base);
		aint[nod] = max(aint[2 * nod],aint[2 * nod + 1]);
	}
	
	void propag(int nod,int st,int dr){
		if(st == dr || !lazy[nod]){
			return;
		}
		
		lazy[2 * nod] += lazy[nod];
		lazy[2 * nod + 1] += lazy[nod];
		aint[2 * nod] += lazy[nod];
		aint[2 * nod + 1] += lazy[nod];
		lazy[nod] = 0;
	}
	
	void update(int nod,int st,int dr,int S,int D,int val){
		propag(nod,st,dr);
		
		if(D < st || S > dr){
			return ;
		}
		
		if(S <= st && dr <= D){
			lazy[nod] += val;
			aint[nod] += val;
			return ;
		}
		
		int mid = (st + dr) / 2;
		
		update(nod * 2,st,mid,S,D,val);
		update(nod * 2 + 1,mid + 1,dr,S,D,val);
		
		aint[nod] = max(aint[2 * nod],aint[2 * nod + 1]);
	}
	
	int query(int nod,int st,int dr,int S,int D){
		propag(nod,st,dr);
		
		if(D < st || S > dr){
			return -1;
		}
		
		if(S <= st && dr <= D){
			return aint[nod];
		}
		
		int mid = (st + dr) / 2;
		return max(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
	}
	
public:
	
	SegmentTree(vector<int> &base,bool enforce_throws = true){
		this->enforce_throws = enforce_throws;
		this->n = base.size();
		aint.resize(4 * n + 1);
		lazy.resize(4 * n + 1);
		build(1,0,n - 1,base);
	}
	
	SegmentTree(int n,bool enforce_throws = true){
		this->enforce_throws = enforce_throws;
		this->n = n;
		aint.resize(4 * n + 1);
		lazy.resize(4 * n + 1);
	}
	
	void update(int st,int dr,int val){
		if(enforce_throws && (st > dr || st < 0 || dr >= n)){
			throw runtime_error("invalid update");
		}
		update(1,0,n - 1,st,dr,val);
	}
	
	int query(int st,int dr){
		if(enforce_throws && (st > dr || st < 0 || dr >= n)){
			throw runtime_error("invalid update");
		}
		
		return query(1,0,n - 1,st,dr);
	}
	
	int overall_max(){
		return aint[1];
	}
	
	void print(){
		for(auto it:aint){
			printf("%d ",it);
		}
		printf("\n");
	}
};

const int NMAX = 2e5;

int n,q;
int father[NMAX + 5];
int lvl[NMAX + 5];
int w[NMAX + 5];
int heavy[NMAX + 5];
int v[NMAX + 5];

int id[NMAX + 5],last_id;
int head[NMAX + 5];

int liniarizare[NMAX + 5],sz;
int fst[NMAX + 5];
int lst[NMAX + 5];

vector<int> graph[NMAX + 5];

vector<int> base;
void predfs(int nod,int tata){
	father[nod] = tata;
	lvl[nod] = 1 + lvl[tata];
	w[nod] = 1;
	
	for(auto it:graph[nod]){
		if(it != tata){
			predfs(it,nod);
			if(w[it] > w[heavy[nod]]){
				heavy[nod] = it;
			}
		}
	}
	
	v[tata] += v[nod];
	w[tata] += w[nod];
}

void dfs(int nod,int tata){
	
	if(!id[nod]){
		id[nod] = ++last_id;
		head[last_id] = nod;
	}
	
	liniarizare[++sz] = nod;
	fst[nod] = sz;
	base.push_back(v[nod]);
	
	if(heavy[nod]){
		id[heavy[nod]] = id[nod];
		dfs(heavy[nod],nod);
	}
	
	for(auto it:graph[nod]){
		if(it == tata || it == heavy[nod]){
			continue;
		}
		
		dfs(it,nod);
	}
	
	lst[nod] = sz;
}

const int LEN = 1 << 13;
char buff[LEN];
int ind = LEN - 1;

int i32(){
	int ans = 0,sgn = 1;
	while(buff[ind] != '-' && (buff[ind] < '0' || buff[ind] > '9')){
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	
	if(buff[ind] == '-'){
		sgn *= -1;
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	
	while(buff[ind] >= '0' && buff[ind] <= '9'){
		ans = ans * 10 + buff[ind] - '0';
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	return ans * sgn;
}

char gc(){
	while(buff[ind] == ' ' || buff[ind] == '\n'){
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	return buff[ind++];
}

int main(){
	
	n = i32();q = i32();
	
	for(int i = 1;i < n;i++){
		int x,y;
		x = i32();y = i32();
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	int sum = 0;
	
	for(int i = 1;i <= n;i++){
		v[i] = i32();
		sum += v[i];
	}
	
	predfs(1,0);
	dfs(1,0);

	SegmentTree t(base);
	
	while(q--){
		char c = gc();
		if(c == 'U'){
			int x,y;
			y = i32();x = i32();
			sum += y;
			
			while(x){
				t.update(fst[head[id[x]]] - 1,fst[x] - 1,y);
				x = father[head[id[x]]];
			}
		}
		else{
			int x;
			x = i32();
			int ans = sum - t.query(fst[x] - 1,lst[x] - 1);
			if(fst[x] != lst[x]){
				ans = max(ans,t.query(fst[x],lst[x] - 1));
			}
			fprintf(g,"%d\n",ans);
		}
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}