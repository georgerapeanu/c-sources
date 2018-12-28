#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int pw3[14];
int dp[1594323];
int cnt[1594323];
char c[20];

int main(){

	// freopen("in","r",stdin);

	pw3[0] = 1;

	for(int i = 1;i <= 13;i++){
		pw3[i] = 3 * pw3[i - 1];
	}

	int t;
	scanf("%d\n",&t);

	while(t--){
		memset(cnt,0,sizeof(cnt));
		int n,k;
		scanf("%d %d\n",&n,&k);
		
		for(int i = 1;i <= n;i++){
			fgets(c,20,stdin);
		
			int val = 0;
			
			for(int i = 0;i < k;i++){
				val += pw3[i] * (c[i] - '0');
			}
			
			cnt[val]++;
		}
		
		for(int mask = 0;mask < pw3[k];mask++){
			int tmp_mask = mask;
			int where = -1;
			dp[mask] = 1 << 28;
			for(int pos = 0;pos < k;tmp_mask /= 3,pos++){
				if(tmp_mask % 3 == 2){
					where = pos;
					dp[mask] = min(dp[mask],1 + max(dp[mask - pw3[pos]],dp[mask - 2 * pw3[pos]]));
				}
			}
			if(where != -1){
				cnt[mask] += cnt[mask - pw3[where]] + cnt[mask - 2 * pw3[where]];
			}
			
			if(cnt[mask] == 1){
				dp[mask] = 0;
			}
		}

		printf("%d\n",dp[pw3[k] - 1]);
	}

	return 0;
}