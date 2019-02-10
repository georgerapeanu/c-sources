#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <vector>
 
using namespace std;
 
FILE *f=fopen("arbint.in","r");
FILE *g=fopen("arbint.out","w");
 
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
 
int n,m;
vector<int> base;
 
int main(){
	
	fscanf(f,"%d %d",&n,&m);
	base.resize(n);
	
	for(int i = 0;i < n;i++){
		fscanf(f,"%d",&base[i]);		
	}
	
	SegmentTree<int> t(base);
	
	
	for(int i = 0;i < m;i++){
		int c,x,y;
		fscanf(f,"%d %d %d",&c,&x,&y);
		
		if(!c){
			x--;
			y--;
			fprintf(g,"%d\n",t.query(x,y));
		}
		else{
			x--;
			t.update(x,x,y - base[x]);
			base[x] = y;
		}
	}
	
    fclose(f);
    fclose(g);
 
    return 0;
}