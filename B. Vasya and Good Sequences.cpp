#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 3e5;
const bool DEBUG = 1;

int n;
int v[NMAX + 5];
int sp[NMAX + 5];
int cnt[NMAX + 5][2];

int main(){
	
	
	if(DEBUG){
		n = 100;
	}
	else{
		scanf("%d",&n);
	}
	cnt[0][0] = 1;
	
	for(int i = 1;i <= n;i++){
		long long a;
		if(DEBUG){
			a = 1;
		}
		else{
			scanf("%lld",&a);
		}
		while(a){
			v[i] += (a & 1);
			a >>= 1;
		}
		sp[i] = sp[i - 1] + v[i];
		cnt[i][0] = cnt[i - 1][0] + (sp[i] % 2 == 0);
		cnt[i][1] = cnt[i - 1][1] + (sp[i] % 2 == 1);
	}
	
	long long ans = 0;
	
	for(int i = 1;i <= n;i++){
		if(i - 64 >= 0){
			ans += cnt[i - 64][sp[i] % 2];
		}
		
		int maxi = 0;
		
		for(int j = i;j > i - 63 && j > 0;j--){
			maxi = max(maxi,v[j]);
			if(2 * maxi <= sp[i] - sp[j - 1] && (sp[i] - sp[j - 1]) % 2 == 0){
				ans++;
			}
		}
	}
	
	printf("%lld",ans);
	
	return 0;
}