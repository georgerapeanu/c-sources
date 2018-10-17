#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <vector>
 
using namespace std;
 
FILE *f=fopen("arbint.in","r");
FILE *g=fopen("arbint.out","w");
 
///tested on https://infoarena.ro/problema/arbint
///0-indexed;
class SegmentTree{
private:
 
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
	
	SegmentTree(vector<int> &base){
		this->n = base.size();
		aint.resize(4 * n + 1);
		lazy.resize(4 * n + 1);
		build(1,0,n - 1,base);
	}
	
	SegmentTree(int n){
		this->n = n;
		aint.resize(4 * n + 1);
		lazy.resize(4 * n + 1);
		vector<int> base = vector<int>(n,0);
		build(1,0,n - 1,base);
	}
	
	void update(int st,int dr,int val){
		if(st > dr || st < 0 || dr >= n){
			throw runtime_error("invalid update");
		}
		update(1,0,n - 1,st,dr,val);
	}
	
	int query(int st,int dr){
		if(st > dr || st < 0 || dr >= n){
			throw runtime_error("invalid update");
		}
		
		return query(1,0,n - 1,st,dr);
	}
	
	void print(){
		for(auto it:aint){
			printf("%d ",it);
		}
		printf("\n");
	}
};
 
int n,m;
vector<int> base;
 
int main(){
	
	fscanf(f,"%d %d",&n,&m);
	base.resize(n);
	
	for(int i = 0;i < n;i++){
		fscanf(f,"%d",&base[i]);		
	}
	
	SegmentTree t(base);
	
	
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