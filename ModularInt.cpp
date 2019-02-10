#include <cstdio>
#include <algorithm>

using namespace std;

///tested on http://codeforces.com/contest/1043/problem/F
///tested on https://codeforces.com/contest/1078/problem/B
///kinda
///teste on https://infoarena.ro/problema/100m for real
class ModularInt{

private:
	static const int MOD = 1e9 + 7;
	
	int val;
	
public:	
	
	ModularInt(){
		val = 0;
	}
	
	ModularInt(int a){
		val = (a % MOD + MOD) % MOD;
	}
		
	ModularInt operator + (const ModularInt &other){
		ModularInt ans(this->val + other.val);
		
		if(ans.val >= MOD){
			ans.val -= MOD;
		}
		
		return ans;
	}
	
	ModularInt operator - (const ModularInt &other){
		ModularInt ans(this->val - other.val);
		
		if(ans.val < 0){
			ans.val += MOD;
		}

		return ans;
	}
	
	ModularInt operator * (const ModularInt &other){
		return ModularInt(1LL * this->val * other.val % MOD);
	}
	
	ModularInt operator / (const ModularInt &other){
		ModularInt ans = 1;
		ModularInt base(other.val);
		int e = MOD - 2;
				
		while(e){
			if(e & 1){
				ans = ans * base;
			}
			base = base * base;
			e >>= 1;
		}
		
		ans = (*this) * ans;
		
		return ans;
	}
	
	bool operator == (const ModularInt &other){
		return this->val == other.val;
	}
	
	bool operator != (const ModularInt &other){
		return this->val != other.val; 
	}

	bool operator < (const ModularInt &other){
		return this->val < other.val;
	}
	
	ModularInt pw(int e){
		ModularInt p = 1;
		ModularInt b = *this;
		
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
		return val;
	}
	
	int toInt(){
		return val;
	}
		
	void print(){
		printf("%d\n",val);
	}
};

ModularInt comb(int n,int k){
	
	if(k > n || k < 0){
		return 0;
	}
	
	ModularInt ans = 1;
	ModularInt reduce = 1;
	
	for(int i = 1;i <= k;i++){
		ans = ans * ModularInt(n - k + i);
		reduce = reduce * ModularInt(i);
	}
		
	ans = ans / reduce;
	
	return ans;
}

const int NMAX = 3e5;

int n;
int cnt[NMAX + 5];

ModularInt dp[8][NMAX + 5];

int main(){
	
	return 0;
}