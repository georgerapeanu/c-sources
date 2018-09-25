#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

FILE *f = fopen("rangemode.in","r");
FILE *g = fopen("rangemode.out","w");

const int NMAX = 1e5;
const int BUCK = 320;

int n,q;
int v[NMAX + 5];
int bucket[NMAX + 5];
int l[NMAX / BUCK + 5];
int r[NMAX / BUCK + 5];

void prepare(int n){
	for(int st = 1,buck = 1;st <= n;st += BUCK,buck++){
		l[buck] = st;
		r[buck] = min(n,st + BUCK - 1);
		for(int dr = l[buck];dr <= r[buck];dr++){
			bucket[dr] = buck;
		}
	}
}

struct query{
	int l,r;
	int id;
	
	bool operator < (const query &other)const{
		if(bucket[l] != bucket[other.l]){
			return bucket[l] < bucket[other.l];
		}
		return r < other.r;
	}
};

query queries[NMAX + 5];
int fr[NMAX + 5];
int ans[NMAX + 5];

int main(){
	
	fscanf(f,"%d %d",&n,&q);
	prepare(n);
	
	for(int i = 1; i <= n; i++){
		fscanf(f,"%d",&v[i]);
	}
	
	for(int i = 1; i <= q; i++){
		fscanf(f,"%d %d",&queries[i].l,&queries[i].r);
		queries[i].id = i;
	}
	
	sort(queries + 1,queries + 1 + q);
	
	int dr,best;
	
	for(int i = 1; i <= q; i++){
		if(bucket[queries[i].l] != bucket[queries[i - 1].l]){
			memset(fr,0,sizeof(fr));
			dr = r[bucket[queries[i].l]];
			best = 0;
		}		
		
		while(dr < queries[i].r){
			fr[v[++dr]]++;
			if(fr[v[dr]] > fr[best] || (fr[v[dr]] == fr[best] && best > v[dr])){
				best = v[dr];
			}
		}
		
		
		int tmp_best = 0;

		int right = min(queries[i].r,r[bucket[queries[i].l]]);
		
		for(int j = queries[i].l;j <= right;j++){
			fr[v[j]]++;
			if(fr[v[j]] > fr[tmp_best] || (fr[v[j]] == fr[tmp_best] && tmp_best > v[j])){
				tmp_best = v[j];
			}
		}
		
		if(fr[tmp_best] > fr[best] || (fr[tmp_best] == fr[best] && tmp_best < best)){
			ans[queries[i].id] = tmp_best;
		}
		
		else{
			ans[queries[i].id] = best;
		}
		
		for(int j = queries[i].l;j <= right;j++){
			fr[v[j]]--;
		}
	}
	
	for(int i = 1;i <= q;i++){
		fprintf(g,"%d\n",ans[i]);
	}
	
	fclose(f);
	fclose(g);
	
    return 0;
}
