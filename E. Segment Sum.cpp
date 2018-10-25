#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const int MOD = 998244353;

int add(int a,int b){
	a += b;
	if(a >= MOD){
		a -= MOD;
	}
	return a;
}

int scad(int a,int b){
	a -= b;
	if(a < 0){
		a += MOD;
	}
	return a;
}

int mult(int a,int b){
	return 1LL * a * b % MOD;
}

long long l,r;
int k;

int dp[20][1 << 10];
int dp2[20][1 << 10];
int cnt[20][1 << 10];
int cnt2[20][1 << 10];
 
bool ok(vector<int> cf){
	vector<int> tmp = cf;
	sort(tmp.begin(),tmp.end());
	return (unique(tmp.begin(),tmp.end()) - tmp.begin()) <= k;
}	

int cnt_bit(int mask){
	int ans = 0;
	while(mask){
		ans += mask & 1;
		mask >>= 1;
	}
	return ans;
}

int pw[20];

int solve(long long val){
	if(!val){
		return 0;
	}
	
	vector<int> cf;
	
	long long cval = val;
	
	while(val){
		cf.push_back(val % 10);
		val /= 10;
	}
	
	reverse(cf.begin(),cf.end());
	
	int ans = mult(ok(cf),cval % MOD);
	
	int p_mask = 0;
	
	int real_pref = 0;
	
	for(int pref = 0;pref < (int)cf.size();pref++){
		for(int c = 0;c < cf[pref];c++){
			if(c == 0 && pref == 0){
				for(int i = 1;i < (int)cf.size();i++){
					for(int mask = 0;mask < (1 << 10);mask++){
						if(cnt_bit(mask) <= k){
							 ans = add(ans,dp2[i][mask]);
						}
					}
				}
				continue;
			}
			int n_mask = p_mask | (1 << c);
			int gaga_pref = add(real_pref,mult(c,pw[(int)cf.size() - pref - 1]));
			for(int mask = 0;mask < (1 << 10);mask++){
				if(cnt_bit(n_mask | mask) <= k){
					ans = add(ans,add(dp[(int)cf.size() - pref - 1][mask],mult(cnt[(int)cf.size() - pref - 1][mask],gaga_pref)));
				}
			}
		}
		p_mask |= (1 << cf[pref]);
		real_pref = add(real_pref,mult(cf[pref],pw[(int)cf.size() - pref - 1]));
	}
	return ans;
}

void precalc(){
	pw[0] = 1;
	for(int i = 1;i <= 19;i++){
		pw[i] = mult(pw[i - 1],10);
	}
	dp[0][0] = 0;
	cnt[0][0] = 1;
	dp2[0][0] = 0;
	cnt2[0][0] = 1;
	
	for(int i = 0;i < 19;i++){
		for(int j = 0;j < (1 << 10);j++){
			for(int k = 0;k < 10;k++){
				cnt[i + 1][j | (1 << k)] = add(cnt[i + 1][j | (1 << k)],cnt[i][j]);
				dp[i + 1][j | (1 << k)] = add(dp[i + 1][j | (1 << k)],add(mult(dp[i][j],10),mult(cnt[i][j],k)));
				if(k || j){
					cnt2[i + 1][j | (1 << k)] = add(cnt2[i + 1][j | (1 << k)],cnt2[i][j]);
					dp2[i + 1][j | (1 << k)] = add(dp2[i + 1][j | (1 << k)],add(mult(dp2[i][j],10),mult(cnt2[i][j],k)));
				}
			}
		}
	}
}

int main(){
	
	cin >> l >> r >> k;
	
	precalc();
	
	// cout << solve(r);
	
	// cout << solve(l - 1);
	
	cout << scad(solve(r),solve(l - 1));
	
	return 0;
}