#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <vector>
#define Debug(...)

using namespace std;

const int kMaxN = 5e5;
const int inf = 1e7;

struct node {
    int lazy;
    int mx;
};

class SegmentTree{
public:
	int n;
	node aint[4 * kMaxN + 5];
	
	void build(int nod,int st,int dr,vector<int> &base){
		aint[nod].lazy = 0;
		if(st == dr){
			aint[nod].mx = base[st - 1];
			return ;
		}
		int mid = (st + dr) / 2;
		build(nod * 2,st,mid,base);
		build(nod * 2 + 1,mid + 1,dr,base);
		refr(nod,st,dr);
	}
	
	void init(vector<int> &base){
		n = base.size();
		build(1,1,n,base);
	}
	
	void refr(int nod,int st,int dr){
		if(st == dr){
			return;
		}
		aint[nod].mx = max(aint[2 * nod].mx,aint[2 * nod + 1].mx);
	}
	
	void propag(int nod,int st,int dr){
		if(st == dr || aint[nod].lazy == 0){
			return ;
		}
		aint[2 * nod].mx += aint[nod].lazy;aint[2 * nod].lazy += aint[nod].lazy;
		aint[2 * nod + 1].mx += aint[nod].lazy;aint[2 * nod + 1].lazy += aint[nod].lazy;
		aint[nod].lazy = 0;
	}
	
	void update(int nod,int st,int dr,int S,int D,int val){
		propag(nod,st,dr);
		if(D < st || dr < S){
			return ;
		}
		if(S <= st && dr <= D){
			aint[nod].mx += val;
			aint[nod].lazy += val;
			return ;
		}
		
		int mid = (st + dr) / 2;
		
		update(nod * 2,st,mid,S,D,val);
		update(nod * 2 + 1,mid + 1,dr,S,D,val);
		refr(nod,st,dr);
	}
	
	int get_val(int nod,int st,int dr,int pos){
		propag(nod,st,dr);
		if(pos < st || pos > dr){
			return -inf;
		}
		if(st == dr){
			return aint[nod].mx;
		}
		
		int mid = (st + dr) / 2;
		
		return max(get_val(nod * 2,st,mid,pos),get_val(nod * 2 + 1,mid + 1,dr,pos));
		
	}
	
	int rightmost(int nod,int st,int dr,int val){
		propag(nod,st,dr);
		if(st == dr){
			return st;
		}
		int mid = (st + dr) / 2;
		if(aint[2 * nod + 1].mx >= val){
			return rightmost(2 * nod + 1,mid + 1,dr,val);
		}
		return rightmost(2 * nod,st,mid,val);
	}
	
	int get_elem(int pos){
		return get_val(1,1,n,pos);
	}
	
	void increment(int l,int r,int val){
		update(1,1,n,l,r,val);
	}
	
	bool query(int start,int fin){
		if(get_elem(fin) == 0){
			return false;
		}
		int val = get_elem(fin);
		int c1 = rightmost(val);
		int c2 = rightmost(val + 1);
		if(c2 >= start)increment(start,c2,-1);
		else c2 = start - 1;
		int rem = (fin - start + 1) - (c2 - start + 1);
		increment(c1 - rem + 1,c1,-1);
		return true;
	}
	
	int rightmost(int val){
		if(aint[1].mx < val){
			return 0;
		}
		return rightmost(1,1,n,val);
	}
}segment_tree;

long long ans = 0;

int n;
vector<int> gr;

bool solve(int n,vector<int> gr){
	sort(gr.begin(),gr.end());
	reverse(gr.begin(),gr.end());
	segment_tree.init(gr);
	
	for(int i = 0;i < n;i++){
		int val = segment_tree.get_elem(i + 1);
		if(i + 1+ val > n){
			return false;
		}			
		if(val == 0){
			continue;
		}
		if(!segment_tree.query(i + 2,i + 1 + val)){
			return false;
		}
	}
	return true;
}

int pseudosolve(int n,vector<int> gr){
	sort(gr.begin(),gr.end());
	reverse(gr.begin(),gr.end());
	segment_tree.init(gr);
	int lol = 0;
	for(int i = 0;i < n;i++){
		int val = segment_tree.get_elem(i + 1);
		if(i + 1+ val > n + 1){
			return -1;
		}			
		if(val == 0){
			continue;
		}
		bool used = false;
		if(i + 1 + val == n + 1){
			val--;
			lol++;
			used = true;
		}
		if(!segment_tree.query(i + 2,i + 1 + val)){
			if(!used){
				val--;
				lol++;
			}
			if(!segment_tree.query(i + 2,i + 1 + val)){
				return -1;
			}
		}
		// for(int i = 1;i <= n;i++){
			// printf("%d ",segment_tree.get_elem(i));
		// }
		// printf("\n");
	}
	return lol;
}

const int LEN = 1e4;
char buff[LEN];
int ind = LEN - 1;

int i32(){
	int ans = 0;
	
	while(buff[ind] < '0' || buff[ind] > '9'){
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,stdin);
		}
	}
	
	while(!(buff[ind] < '0' || buff[ind] > '9')){
		ans = ans * 10 + buff[ind] - '0';
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,stdin);
		}
	}
	return ans;
}

int main(){
	
	n = i32();

	gr.resize(n);
	
	long long sum = 0;
	
	for(int i = 0;i < n;i++){
		gr[i] = i32();
		sum += gr[i];
	}
	
	int tmp = pseudosolve(n,gr);
	if(tmp == -1){
		printf("-1");
		return 0;
	}
	
	n++;
	int st = tmp,dr = tmp;
	for(int pas = 1 << 20;pas;pas >>= 1){
		if(dr + pas < n){
			gr.push_back(dr + pas);
			if(solve(n,gr)){
				dr += pas;
			}
			gr.pop_back();
		}			
		if(st - pas >= 0){
			gr.push_back(st - pas);
			
			if(solve(n,gr)){
				st -= pas;
			}
			gr.pop_back();
		}
	}
	
	for(int i = st;i <= dr;i += 2){
		printf("%d ",i);
	}
	
	
	return 0;
}