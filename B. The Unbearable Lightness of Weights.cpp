#include <iostream>
#include <cstdio>

using namespace std;


class BimodularInt{

private:
	static const int MOD1 = 1e9 + 7;
	static const int MOD2 = 666013;
	
	int h1,h2;
	
	BimodularInt(int h1,int h2){
		this->h1 = h1;
		this->h2 = h2;
	}
	
public:	
	
	BimodularInt(){
		h1 = h2 = 0;
	}
	
	BimodularInt(int a){
		h1 = (a % MOD1 + MOD1) % MOD1;
		h2 = (a % MOD2 + MOD2) % MOD2;
	}
		
	BimodularInt operator + (const BimodularInt &other){
		BimodularInt ans(this->h1 + other.h1,this->h2 + other.h2);
		
		if(ans.h1 >= MOD1){
			ans.h1 -= MOD1;
		}
		
		if(ans.h2 >= MOD2){
			ans.h2 -= MOD2;
		}
		
		return ans;
	}
	
	BimodularInt operator - (const BimodularInt &other){
		BimodularInt ans(this->h1 - other.h1,this->h2 - other.h2);
		
		if(ans.h1 < 0){
			ans.h1 += MOD1;
		}
		
		if(ans.h2 < 0){
			ans.h2 += MOD2;
		}
		
		return ans;
	}
	
	BimodularInt operator * (const BimodularInt &other){
		return BimodularInt(1LL * this->h1 * other.h1 % MOD1,1LL * this->h2 * other.h2 % MOD2);
	}
	
	BimodularInt operator / (const BimodularInt &other){
		BimodularInt ans = 1;
		BimodularInt base1(other.h1,1);
		BimodularInt base2(1,other.h2);
		int e1 = MOD1 - 2,e2 = MOD2 - 2;
				
		while(e1){
			if(e1 & 1){
				ans = ans * base1;
			}
			base1 = base1 * base1;
			e1 >>= 1;
		}
		
		while(e2){
			if(e2 & 1){
				ans = ans * base2;
			}
			base2 = base2 * base2;
			e2 >>= 1;
		}
		
		ans = (*this) * ans;
		
		return ans;
	}
	
	bool operator == (const BimodularInt &other){
		return this->h1 == other.h1 && this->h2 == other.h2;
	}
	
	bool operator != (const BimodularInt &other){
		return this->h1 != other.h1 || this->h2 != other.h2; 
	}

	bool operator < (const BimodularInt &other){
		if(this->h1 != other.h1){
			return this->h1 < other.h1;
		}
		return this->h2 != other.h2;
	}
	
	BimodularInt pw(int e){
		BimodularInt p = 1;
		BimodularInt b = *this;
		
		while(e){
			if(e & 1){
				p = p * b;
			}
			b = b * b;
			e >>= 1;
		}
		
		return p;
	}
	
	bool is0(){
		return h1 || h2;
	}
		
	void print(){
		printf("%d %d\n",h1,h2);
	}
	
};

BimodularInt fact[105];
BimodularInt ifact[105];

BimodularInt comb(int n,int k){
	
	if(k > n || k < 0){
		return 0;
	}
	
	return fact[n] * ifact[k] * ifact[n - k];
}

int n;
BimodularInt dp[2][105][10005];
int fr[105];

int main(){
	
	fact[0] = 1;
	
	for(int i = 1;i <= 100;i++){
		fact[i] = BimodularInt(i) * fact[i - 1];
	}
	
	
	ifact[100] = BimodularInt(1) / fact[100];
	
	for(int i = 99;i >= 0;i--){
		ifact[i] = BimodularInt(i + 1) * ifact[i + 1];
	}
	
	
	dp[0][0][0] = 1;
	
	
	cin >> n;
	
	int t1 = -1;
	int t2 = -1;
	
	for(int i = 1;i <= n;i++){
		int x;
		cin >> x;
		fr[x]++;
		
		if(t1 == -1){
			t1 = x;
		}
		else if(t2 == -1 && x != t1){
			t2 = x;
		}
		
		for(int j = 0;j <= 100;j++){
			for(int k = 0;k <= 10000;k++){
				dp[i & 1][j][k] = dp[(i & 1) ^ 1][j][k];
				if(k >= x && j){
					dp[i & 1][j][k] = dp[(i & 1) ^ 1][j - 1][k - x] + dp[i & 1][j][k];
				}
			}
		}
	}
	
	int ans = 0;
	
	
	if(t1 != -1 && t2 != -1 && fr[t1] + fr[t2] == n){
		if(dp[n & 1][fr[t1]][fr[t1] * t1] == BimodularInt(1) || dp[n & 1][fr[t2]][fr[t2] * t2] == BimodularInt(1)){
			ans = n;
		}
	}
		
	for(int i = 0;i <= 100;i++){
		for(int j = 0;j <= fr[i];j++){
			if(dp[n & 1][j][j * i] == comb(fr[i],j)){
				ans = max(ans,j);
			}
		}
	}
	
	cout << ans;
	
	return 0;
}