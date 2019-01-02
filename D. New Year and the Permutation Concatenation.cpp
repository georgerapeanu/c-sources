#include <cstdio>

const int MOD = 998244353;

using namespace std;

int main(){
	int ans = 0;
	int n;
	scanf("%d",&n);
	int delta = 1;
	for(int i = n;i > 1;i--){
		delta = 1LL * delta * i % MOD;
		ans = ((long long)ans + MOD - delta) % MOD;
	}
	ans = (ans + 1LL * n * delta) % MOD;
	printf("%d",ans);
	
	return 0;
}