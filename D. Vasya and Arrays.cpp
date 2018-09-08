#include <cstdio>

using namespace std;

int n,m;
int A[300005];
int B[300005];
long long SPA[300005];
long long SPB[300005];

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&A[i]);
		SPA[i] = A[i] + SPA[i - 1];
	}
	
	scanf("%d",&m);
	
	for(int i = 1;i <= m;i++){
		scanf("%d",&B[i]);
		SPB[i] = B[i] + SPB[i - 1];
	}
	
	if(SPA[n] != SPB[m]){
		printf("-1");
		return 0;
	}
	
	int i = 1,j = 1;
	int ans = 0;
	while(i <= n && j <= m){
		if(SPA[i] < SPB[j]){
			i++;
		}
		else if(SPA[i] > SPB[j]){
			j++;
		}
		else{
			i++;
			j++;
			ans++;
		}
	}
	
	printf("%d",(ans == 0 ? -1 : ans));
	
	return 0;
}