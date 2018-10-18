#include <cstdio>
#include <algorithm>
#include <vector>
#include <stdexcept>

using namespace std;

FILE *f = fopen("parcele.in","r");
FILE *g = fopen("parcele.out","w");

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
	
	SegmentTree t(XMAX + 5,false);
	
	for(int i = 0;i <= XMAX;i++){
		for(auto it:ev_x[i]){
			t.update(it,it + dy - 1,1);
		}
		
		if(i >= dx){
			for(auto it:ev_x[i - dx]){
				t.update(it,it + dy - 1,-1);
			}
		}
		
		ans_x[i] = t.overall_max();
	}
	
	t = SegmentTree(XMAX + 5,false);
	
	for(int i = 0;i <= XMAX;i++){
		for(auto it:ev_y[i]){
			t.update(it,it + dx - 1,1);
		}
		
		if(i >= dy){
			for(auto it:ev_y[i - dy]){
				t.update(it,it + dx - 1,-1);
			}
		}
		
		ans_y[i] = t.overall_max();
	}
	
	int rez = 0;
	
	solve(ans_x,dx,rez);
	solve(ans_y,dy,rez);
	
	fprintf(g,"%d",rez);
	
	fclose(f);
	fclose(g);
	
	return 0;
}