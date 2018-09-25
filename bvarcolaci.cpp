#include <cstdio>
#include <vector>

using namespace std;

FILE *f = fopen("bvarcolaci.in","r");
FILE *g = fopen("bvarcolaci.out","w");

const int NMAX = 25e4;

int n;
int v[NMAX + 5];

long long ans = 0;
int maj[NMAX + 5],sz_maj;
bool is[NMAX + 5];
int fr[NMAX + 5];
int sums[2 * NMAX + 5],stq = NMAX + 2,drq = NMAX + 1;

void solve(int st,int dr){
	if(st == dr){
		ans++;
		return;
	}
	int mid = (st + dr) / 2;
	solve(st,mid);
	solve(mid + 1,dr);
	sz_maj = 0;
		
	for(int i = mid; i >= st; i--){
		fr[v[i]]++;
		if(!is[v[i]] && fr[v[i]] >= (mid - i + 1) / 2 + 1){
			maj[++sz_maj] = v[i];
			is[v[i]] = 1;
		}
	}
	
	for(int i = mid; i >= st; i--){
		fr[v[i]] = 0;
	}
	
	for(int i = mid + 1; i <= dr; i++){
		fr[v[i]]++;
		if(!is[v[i]] && fr[v[i]] >= (i - mid) / 2 + 1){
			maj[++sz_maj] = v[i];
			is[v[i]] = 1;
		}
	}
	
	for(int i = mid + 1; i <= dr; i++){
		fr[v[i]] = 0;
	}
	
	for(int i = 1; i <= sz_maj; i++){
		int it = maj[i];
		is[it] = 0;
		stq = NMAX + 2,drq = NMAX + 1;
		int base = 0,lvl = 0;
		sums[++drq] = 1;
		for(int i = st;i < mid;i++){
			lvl += (it == v[i] ? 1:-1);
			if(lvl < base){
				sums[--stq] = 0;
				base--;
			}
			
			else if(lvl - base >= drq - stq + 1){
				sums[++drq] = 0;;
			}
			
			sums[lvl - base + stq]++;
		}
		
		lvl += (v[mid] == it ? 1 : -1);
		
		for(int i = stq + 1;i <= drq;i++){
			sums[i] += sums[i - 1];
		}
						
		for(int i = mid + 1;i <= dr;i++){
			lvl += (it == v[i] ? 1:-1);
			if(lvl <= base){
				continue;
			}
			
			if(lvl - base >= drq - stq + 1){
				ans += sums[drq];
			}
			
			else{
				ans += sums[lvl - base - 1 + stq];
			}
		}
	}
}

const int LEN = 1 << 15;
char buff[LEN];
int ind = LEN - 1;

int i32(){
	int ans = 0;
	
	while(buff[ind] < '0' || buff[ind] > '9'){
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	
	while(buff[ind] >= '0' && buff[ind] <= '9'){
		ans = ans * 10 + (buff[ind] - '0');
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	
	return ans;
}

int main(){
	
	n = i32();
	
	for(int i = 1; i <= n; i++){
		v[i] = i32();
	}
	
	solve(1,n);
	
	fprintf(g,"%lld",ans);
	
	return 0;
}