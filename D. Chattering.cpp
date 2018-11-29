#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 1e5;
const int LGMAX = 18;


struct minupd{
	int worst = 1 << 30;
	int join(int a,int b){return min(a,b);}
};

struct maxupd{
	int worst = - (1 << 30);
	int join(int a,int b){return max(a,b);}
};

template <typename upd_t>
class SegmentTree{

public:

	upd_t upd;
	int tree[12 * NMAX + 5];
	
	void build(int v[],int nod,int st,int dr){
		if(st == dr){
			tree[nod] = v[st];
			return ;
		}
		int mid = (st + dr) / 2;
		build(v,nod * 2,st,mid);
		build(v,nod * 2 + 1,mid + 1,dr);
		tree[nod] = upd.join(tree[2 * nod],tree[2 * nod + 1]);
	}
	
	
	int query(int nod,int st,int dr,int S,int D){
		if(S <= st && dr <= D){
			return tree[nod];
		}
		
		if(dr < S || D < st){
			return upd.worst;
		}
		
		int mid = (st + dr) / 2;
		
		return upd.join(query(2 * nod,st,mid,S,D),
					query(2 * nod + 1,mid + 1,dr,S,D));
	}
};

int n;
int v[3 * NMAX + 5];

int left[LGMAX + 1][3 * NMAX + 1];
int right[LGMAX + 1][3 * NMAX + 1];

SegmentTree<minupd> l[LGMAX + 1];
SegmentTree<maxupd> r[LGMAX + 1];

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
	
	while(buff[ind] >= '0' && buff[ind] <= '9'){
		ans = ans * 10 + (buff[ind] - '0');
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,stdin);
		}
	}
	return ans;
}

int main(){
	
	n = i32();

	for(int i = 1;i <= n;i++){
		v[i] = i32();
	}
	
	for(int i = n + 1;i <= 3 * n;i++){
			v[i] = v[i - n];
	}
	
	for(int i = 1;i <= 3 * n;i++){
		left[0][i] = max(1,i - v[i]);
		right[0][i] = min(3 * n,i + v[i]);
	}
	
	for(int i = 1;i <= LGMAX;i++){
		l[i - 1].build(left[i - 1],1,1,3 * n);
		r[i - 1].build(right[i - 1],1,1,3 * n);
		for(int j = 1;j <= 3 * n;j++){
			int range_st = left[i - 1][j];
			int range_dr = right[i - 1][j];
			left[i][j] = (left[i - 1][j] == 1 ? 1:l[i - 1].query(1,1,3 * n,range_st,range_dr));
			right[i][j] = (right[i - 1][j] == 3 * n ? 3 * n:r[i - 1].query(1,1,3 * n,range_st,range_dr));
		}
	}
	
	l[LGMAX].build(left[LGMAX],1,1,3 * n);
	r[LGMAX].build(right[LGMAX],1,1,3 * n);
	
	for(int i = n + 1;i <= 2 * n;i++){
		int range_st = i;
		int range_dr = i;
		int ans = 0;
		for(int bit = LGMAX;bit >= 0;bit--){
			int new_range_st = (range_st == 1 ? 1:l[bit].query(1,1,3 * n,range_st,range_dr));
			int new_range_dr = (range_dr == 3 * n ? 3 * n:r[bit].query(1,1,3 * n,range_st,range_dr));
			if(new_range_dr - new_range_st + 1 < n){
				range_st = new_range_st;
				range_dr = new_range_dr;
				ans |= (1 << bit);
				
			}	
		}
		printf("%d ",ans + 1);
	}
	
	return 0;
}