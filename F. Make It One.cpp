#include <cstdio>
#include <algorithm>

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
	
	operator bool(){
		return h1 || h2;
	}
	
	void print(){
		printf("%d %d\n",h1,h2);
	}
	
};

BimodularInt comb(int n,int k){
	
	if(k > n || k < 0){
		return 0;
	}
	
	BimodularInt ans = 1;
	BimodularInt reduce = 1;
	
	for(int i = 1;i <= k;i++){
		ans = ans * BimodularInt(n - k + i);
		reduce = reduce * BimodularInt(i);
	}
		
	ans = ans / reduce;
	
	return ans;
}

const int NMAX = 3e5;

int n;
int cnt[NMAX + 5];

BimodularInt dp[8][NMAX + 5];

int main(){
	
	scanf("%d",&n);

	for(int i = 1;i <= n;i++){
		int val;
		scanf("%d",&val);
		cnt[val]++;
	}
	
	for(int i = 1;i <= NMAX;i++){
		for(int j = 2 * i;j <= NMAX;j += i){
			cnt[i] += cnt[j];
		}
	}

	for(int i = 1;i <= 7;i++){
		for(int j = NMAX;j;j--){
			dp[i][j] = comb(cnt[j],i);
			
			for(int k = 2 * j;k <= NMAX;k += j){
				dp[i][j] = dp[i][j] - dp[i][k];
			}
		}
		
		if(dp[i][1]){
			printf("%d",i);
			return 0;
		}
	}
	
	printf("-1");
	
	return 0;
}