#define JUDGE 0

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>

using namespace std;


const int NMAX = 5e5;
const int LGMAX = 19;
	
int sa[NMAX + 5];
int order[LGMAX + 1][NMAX + 5];
int gap;

int n;
char c[NMAX + 5];
int dp[NMAX + 5];

int cmp(int a,int b){
	if(order[gap - 1][a] != order[gap - 1][b]){
		return (order[gap - 1][a] < order[gap - 1][b] ? -1:1);
	}
	
	a += (1 << (gap - 1));
	b += (1 << (gap - 1));
	
	if(a <= n && b <= n){
		if(order[gap - 1][a] == order[gap - 1][b]){
			return 0;
		}
		
		return (order[gap - 1][a] < order[gap - 1][b] ? -1:1);
	}
	
	return (a > b ? -1:1);
}

bool cmp2(int a,int b){
	return cmp(a,b) < 0;
}

void build_sa(){
		
	for(int i = 1;i <= n;i++){
		sa[i] = i;
	}
	
	sort(sa + 1,sa + 1 + n,[&](int a,int b){return c[a] < c[b];});
	
	
	order[0][sa[1]] = 1;
	for(int i = 2;i <= n;i++){
		order[0][sa[i]] = order[0][sa[i - 1]] + (c[sa[i]] != c[sa[i - 1]]);
	}
	
	for(gap = 1;gap <= LGMAX;gap++){
		sort(sa + 1,sa + 1 + n,cmp2);
		order[gap][sa[1]] = 1;
		for(int i = 2;i <= n;i++){
			order[gap][sa[i]] = order[gap][sa[i - 1]] + (cmp(sa[i - 1],sa[i]) != 0);
		}
	}
}

int lcp(int i,int j){
	int ans = 0;
	for(int l = LGMAX;l >= 0;l--){
		if(i <= n && j <= n && order[l][i] == order[l][j]){
			ans += 1 << l;
			i += (1 << l);
			j += (1 << l);
		}
	}
	return ans;
}

void print_sa(){
	for(int i = 1;i <= n;i++){
		printf("%d ",sa[i]);
	}
	printf("\n");
}

int aint[4 * NMAX + 5];

void build(int nod,int st,int dr){
	aint[nod] = -1;
	if(st == dr){
		return;
	}
	int mid = (st + dr) / 2;
	build(nod,st,mid);
	build(nod,mid + 1,dr);
}

void update(int nod,int st,int dr,int pos,int val){
	if(st > pos || dr < pos){
		return ;
	}
	
	if(st == dr){
		aint[nod] = val;
		return ;
	}
	
	int mid = (st + dr) / 2;
	
	update(nod * 2,st,mid,pos,val);
	update(nod * 2 + 1,mid + 1,dr,pos,val);
	aint[nod] = max(aint[2 * nod],aint[2 * nod + 1]);
}

int query(int nod,int st,int dr,int S,int D){
	if(D < st || S > dr){
		return -1;
	}
	
	if(S <= st && dr <= D){
		return aint[nod];
	}
	
	int mid = (st + dr) / 2;
	
	return max(query(nod * 2,st,mid,S,D),query(nod * 2 + 1,mid + 1,dr,S,D));
}

int main(){
	if(!JUDGE){
		freopen("in","r",stdin);
		freopen("out","w",stdout);
	}
	
	fscanf(stdin,"%d\n",&n);
	fgets(c + 1,n + 5,stdin);
	build_sa();
	build(1,1,n);
	
	int last_inserted = n + 1;
	
	int ans = 0;
	
	for(int i = n;i;i--){
		dp[i] = dp[i + 1] + 1;
		int st1 = order[LGMAX][i],dr1 = order[LGMAX][i];
		int st2 = order[LGMAX][i + 1],dr2 = order[LGMAX][i + 1];
		
		while(dp[i] > 1){
			
			int st,dr;
			
			st = 0,dr = st1;
			
			while(dr - st > 1){
				int mid = (st + dr) / 2;
				if(lcp(sa[mid],i) >= dp[i] - 1){
					dr = mid;
				}
				else{
					st = mid;
				}
			}
			
			st1 = dr;

			st = dr1,dr = n + 1;
			
			while(dr - st > 1){
				int mid = (st + dr) / 2;
				if(lcp(sa[mid],i) >= dp[i] - 1){
					st = mid;
				}
				else{
					dr = mid;
				}
			}
			
			dr1 = st;
			
			st = 0,dr = st2;
			
			while(dr - st > 1){
				int mid = (st + dr) / 2;
				if(lcp(sa[mid],i + 1) >= dp[i] - 1){
					dr = mid;
				}
				else{
					st = mid;
				}
			}
			
			st2 = dr;
				
			st = dr2,dr = n + 1;
			
			while(dr - st > 1){
				int mid = (st + dr) / 2;
				if(lcp(sa[mid],i + 1) >= dp[i] - 1){
					st = mid;
				}
				else{
					dr = mid;
				}
			}
			
			dr2 = st;
			
			if(query(1,1,n,st1,dr1) >= dp[i] - 1 || query(1,1,n,st2,dr2) >= dp[i] - 1){
				break;
			}
			last_inserted--;

			update(1,1,n,order[LGMAX][last_inserted],dp[last_inserted]);
			dp[i]--;
		}
		ans = max(ans,dp[i]);
	}
		
	fprintf(stdout,"%d",ans);
	
	return 0;
}