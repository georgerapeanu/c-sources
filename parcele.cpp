	
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stdexcept>
 
using namespace std;
 
FILE *f = fopen("parcele.in","r");
FILE *g = fopen("parcele.out","w");
 
///tested on https://infoarena.ro/problema/arbint
///tested on https://infoarena.ro/problema/parcele
///0-indexed;
template<typename tp>
class SegmentTree{
private:
 
	bool enforce_throws;
	int n;
	tp neutral_aint;
	tp neutral_lazy;
	vector<tp> aint;
	vector<tp> lazy;
 
	///change these
	
	tp join(tp a,tp b){
		return max(a,b);
	}
	
	tp change(tp a,tp b){///change a by operating it with b
		return a + b;
	}
	
	void propag(int nod,int st,int dr){
		if(st == dr || lazy[nod] == neutral_lazy){
			return;
		}
		
		lazy[2 * nod] = change(lazy[2 * nod],lazy[nod]);
		lazy[2 * nod + 1] = change(lazy[2 * nod + 1],lazy[nod]);
		aint[2 * nod] = change(aint[2 * nod],lazy[nod]);
		aint[2 * nod + 1] = change(aint[2 * nod + 1],lazy[nod]);
		lazy[nod] = neutral_lazy;
	}
	
	///
	
	void build(int nod,int st,int dr,vector<tp> &base){
		lazy[nod] = neutral_lazy;
		aint[nod] = neutral_aint;
		
		if(st == dr){
			aint[nod] = base[st];
			return;
		}
		
		int mid = (st + dr) / 2;
		
		build(nod * 2,st,mid,base);
		build(nod * 2 + 1,mid + 1,dr,base);
		aint[nod] = join(aint[2 * nod],aint[2 * nod + 1]);
	}
	
	
	void update(int nod,int st,int dr,int S,int D,tp val){
		propag(nod,st,dr);
		
		if(D < st || S > dr){
			return ;
		}
		
		if(S <= st && dr <= D){
			lazy[nod] = change(lazy[nod],val);
			aint[nod] = change(aint[nod],val);
			return ;
		}
		
		int mid = (st + dr) / 2;
		
		update(nod * 2,st,mid,S,D,val);
		update(nod * 2 + 1,mid + 1,dr,S,D,val);
		
		aint[nod] = join(aint[2 * nod],aint[2 * nod + 1]);
	}
	
	tp query(int nod,int st,int dr,int S,int D){
		propag(nod,st,dr);
		
		if(D < st || S > dr){
			return -1;
		}
		
		if(S <= st && dr <= D){
			return aint[nod];
		}
		
		int mid = (st + dr) / 2;
		return join(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
	}
	
public:
	
	SegmentTree(vector<tp> &base,tp neutral_aint = 0,tp neutral_lazy = 0,bool enforce_throws = true){
		this->enforce_throws = enforce_throws;
		this->n = base.size();
		this->neutral_aint = neutral_aint;
		this->neutral_lazy = neutral_lazy;
		aint.resize(4 * n + 1);
		lazy.resize(4 * n + 1);
		build(1,0,n - 1,base);
	}
	
	SegmentTree(int n,tp neutral_aint = 0,tp neutral_lazy = 0,bool enforce_throws = true){
		this->enforce_throws = enforce_throws;
		this->n = n;
		this->neutral_aint = neutral_aint;
		this->neutral_lazy = neutral_lazy;
		aint = vector<tp>(4 * n + 1,neutral_aint);
		lazy = vector<tp>(4 * n + 1,neutral_lazy);
	}
	
	void update(int st,int dr,tp val){
		if(enforce_throws && (st > dr || st < 0 || dr >= n)){
			throw runtime_error("invalid update");
		}
		update(1,0,n - 1,st,dr,val);
	}
	
	tp query(int st,int dr){
		if(enforce_throws && (st > dr || st < 0 || dr >= n)){
			throw runtime_error("invalid update");
		}
		
		return query(1,0,n - 1,st,dr);
	}
	
	tp overall(){
		return aint[1];
	}
	
	// void print(){
		// for(auto it:aint){
			// printf("%d ",it);
		// }
		// printf("\n");
	// }
};
 
 
const int NMAX = 1e5;
const int XMAX = 1.5e5;
 
int dx,dy;
int n;
 
vector<int> ev_x[XMAX + 5];
vector<int> ev_y[XMAX + 5];
 
int ans_x[XMAX + 5];
int ans_y[XMAX + 5];
 
void solve(int ans[],int d,int &rez){
	int left[XMAX + 5];
	int right[XMAX + 5];
	
	left[0] = ans[0];
	
	for(int i = 1;i <= XMAX + 3;i++){
		left[i] = max(left[i - 1],ans[i]);
	}
	
	right[XMAX + 4] = ans[XMAX];
	
	for(int i = XMAX + 3;i >= 0;i--){
		right[i] = max(right[i + 1],ans[i]);
	}
	
	for(int i = 0;i <= XMAX;i++){
		rez = max(rez,left[i] + (i + d <= XMAX ? right[i + d]:0));
		rez = max(rez,right[i] + (i - d >= 0 ? left[i - d]:0));
	}
}
 
const int LEN = 1 << 14;
char buff[LEN];
int ind = LEN - 1;
 
int i32(){
	int ans = 0;
	
	while(buff[ind] < '0' || buff[ind] > '9'){
		if(++ind >= LEN){
			fread(buff,1,LEN,f);
			ind = 0;
		}
	}
	
	while(buff[ind] >= '0' && buff[ind] <= '9'){
		ans = ans * 10 + (buff[ind] - '0');
		if(++ind >= LEN){
			fread(buff,1,LEN,f);
			ind = 0;
		}
	}
	
	return ans;
}
 
int main(){
	
	fscanf(f,"%d %d",&dx,&dy);
	fscanf(f,"%d",&n);
	
	dx++;
	dy++;
 
	for(int i = 1;i <= n;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		ev_x[x].push_back(y);
		ev_y[y].push_back(x);
	}
	
	SegmentTree<int> t(XMAX + 5,0,0,false);
	
	for(int i = 0;i <= XMAX;i++){
		for(auto it:ev_x[i]){
			t.update(it,it + dy - 1,1);
		}
		
		if(i >= dx){
			for(auto it:ev_x[i - dx]){
				t.update(it,it + dy - 1,-1);
			}
		}
		
		ans_x[i] = t.overall();
	}
	
	t = SegmentTree<int>(XMAX + 5,0,0,false);
	
	for(int i = 0;i <= XMAX;i++){
		for(auto it:ev_y[i]){
			t.update(it,it + dx - 1,1);
		}
		
		if(i >= dy){
			for(auto it:ev_y[i - dy]){
				t.update(it,it + dx - 1,-1);
			}
		}
		
		ans_y[i] = t.overall();
	}
	
	int rez = 0;
	
	solve(ans_x,dx,rez);
	solve(ans_y,dy,rez);
	
	fprintf(g,"%d",rez);
	
	fclose(f);
	fclose(g);
	
	return 0;
}