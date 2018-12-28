#include <cstdio>
#include <algorithm>

using namespace std;

long long gauss[100000];

void print(long long val){
	while(val){
		printf("%d",(val&1));
		val >>= 1;
	}
	printf("\n");
}

int main(){
	
	int t;	
	scanf("%d",&t);
	
	while(t--){
		int n;
		scanf("%d",&n);
		long long total_xor = 0;
		for(int i = 0;i < n;i++){
			scanf("%lld",&gauss[i]);
			total_xor ^= gauss[i];
		}
		
		int lin = 0,col = 63;
		
		while(lin < n && col >= 0){
			bool found = false;
			
			for(int i = lin;i < n;i++){
				if((gauss[i] >> col) & 1){
					swap(gauss[lin],gauss[i]);
					found = true;
					break;
				}
			}
			
			if(!found){
				col--;
				continue;
			}
			
			for(int i = 0;i < n;i++){
				if(i == lin){
					continue;
				}
				if(gauss[i] & (1LL << col)){
					gauss[i] ^= gauss[lin];
				}
			}
			
			lin++;col--;
		}
		
		long long ans = 1e18;
		
		for(int i = 0;i < lin;i++){
			ans = min(ans,abs(gauss[i] - (total_xor ^ gauss[i])));
		}
		
		printf("%lld\n",ans);
		
		print(total_xor);
		for(int i = 0;i < lin;i++){
			print(gauss[i]);
		}
	}
	
	return 0;
}