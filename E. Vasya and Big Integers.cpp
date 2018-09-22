#include <cstdio>
#include <cstring>

using namespace std;

const int NMAX = 1e6;
const int LGMAX = 19;

int MOD1;
int MOD2;
int BASE;
int pw1[NMAX + 1];
int pw2[NMAX + 1];


struct hsh_t{
	
	int len;
	int h1;
	int h2;
	
	
	
	static void init(){
		MOD1 = 666013;
		MOD2 = 1e9 + 7;
		BASE = 31;
		
		pw1[0] = pw2[0] = 1;
		for(int i = 1;i <= NMAX;i++){
			pw1[i] = 1LL * pw1[i - 1] * BASE % MOD1;
			pw2[i] = 1LL * pw2[i - 1] * BASE % MOD2;
		}
	}
	
	hsh_t(){
		len = h1 = h2 = 0;
	}
	
	hsh_t(char c){
		len = 1;
		h1 = ((c - '0')) % MOD1;
		h2 = ((c - '0')) % MOD2;
	}
	
	hsh_t operator + (const hsh_t &other)const{
		hsh_t ans;
		ans.len = this->len + other.len;
		ans.h1 = (1LL * this->h1 * pw1[other.len] + other.h1) % MOD1;
		ans.h2 = (1LL * this->h2 * pw2[other.len] + other.h2) % MOD2;
		return ans;
	}
	
	bool operator == (const hsh_t &other)const{
		return this->h1 == other.h1 && this->h2 == other.h2 && this->len == other.len;
	}
};


int n;
int l_sz;
int r_sz;
char a[NMAX + 1];
char l[NMAX + 1];
char r[NMAX + 1];

int dp[NMAX + 1];

int aib[NMAX + 1];

hsh_t TA[LGMAX + 1][NMAX + 1];
hsh_t TL[LGMAX + 1][NMAX + 1];
hsh_t TR[LGMAX + 1][NMAX + 1];


const int MOD = 998244353;
void add(int &a,int b){
	a += b;
	if(a >= MOD){
		a -= MOD;
	}
}

void u(int pos,int val){
	for(;pos <= n;pos += (-pos) & pos){
		add(aib[pos],val);
	}
}

int q(int pos){
	if(pos < 0){
		return 0;
	}
	int ans = 1;
	for(;pos;pos -= (-pos) & pos){
		add(ans,aib[pos]);
	}
	return ans;
}

int main(){
	///do not forgetti
	// freopen("in","r",stdin);
	// freopen("out","w",stdout);
	///
	
	hsh_t::init();
	
	fgets(a + 1,NMAX + 1,stdin);
	fgets(l + 1,NMAX + 1,stdin);
	fgets(r + 1,NMAX + 1,stdin);
	
	n = strlen(a + 1);while(!('0' <= a[n] && a[n] <= '9'))n--;
	l_sz = strlen(l + 1);while(!('0' <= l[l_sz] && l[l_sz] <= '9'))l_sz--;
	r_sz = strlen(r + 1);while(!('0' <= r[r_sz] && r[r_sz] <= '9'))r_sz--;
	
	for(int i = 1;i <= n;i++){
		TA[0][i] = hsh_t(a[i]);
	}
	
	for(int i = 1;i <= l_sz;i++){
		TL[0][i] = hsh_t(l[i]);
	}
	
	for(int i = 1;i <= r_sz;i++){
		TR[0][i] = hsh_t(r[i]);
	}
	
	for(int i = 1;i <= LGMAX;i++){
		for(int j = 1;j <= n - (1 << i) + 1;j++){
			TA[i][j] = TA[i - 1][j] + TA[i - 1][j + (1 << (i - 1))];
		}
	}

	for(int i = 1;i <= LGMAX;i++){
		for(int j = 1;j <= l_sz - (1 << i) + 1;j++){
			TL[i][j] = TL[i - 1][j] + TL[i - 1][j + (1 << (i - 1))];
		}
	}
	
	for(int i = 1;i <= LGMAX;i++){
		for(int j = 1;j <= r_sz - (1 << i) + 1;j++){
			TR[i][j] = TR[i - 1][j] + TR[i - 1][j + (1 << (i - 1))];
		}
	}
		
	for(int i = 1;i <= n;i++){
		if(i < l_sz){
			continue;
		}
		
		int right,left;
		
		int ind = i - l_sz,ans = 0;
		
		for(int j = LGMAX;j >= 0;j--){
			if(ans + (1 << j) <= l_sz && TL[j][ans + 1] == TA[j][ind + 1]){
				ind += (1 << j);
				ans += (1 << j);
			}
		}
		
		if(ans == l_sz || (a[ind + 1] > l[ans + 1])){
			right = i - l_sz;
		}
		
		else{
			right = i - l_sz - 1;
		}
	
		if(i >= r_sz){
			ind = i - r_sz,ans = 0;
			
			for(int j = LGMAX;j >= 0;j--){
				if(ans + (1 << j) <= r_sz && TR[j][ans + 1] == TA[j][ind + 1]){
					ind += (1 << j);
					ans += (1 << j);
				}
			}
			
			if(ans == r_sz || (a[ind + 1] < r[ans + 1])){
				left = i - r_sz;
			}
			
			else{
				left = i - r_sz + 1;
			}
		}
		
		else{
			left = 0;
		}
				
		if(left > right){
			continue;
		}
			
		
		dp[i] = q(right) - q(left - 1);
		if(dp[i] < 0)dp[i] += MOD;
		if(right == i - 1 && a[i] == '0'){
			add(dp[i],dp[i - 1]);
		}
		if(a[i + 1] != '0'){
			u(i,dp[i]);
		}
	}
	
	printf("%d",dp[n]);
	
	return 0;
}