#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

const int VMAX = 1.5e7;

int n;
int fr[VMAX + 5];
int cnt[VMAX + 5];
bool e[VMAX + 5];
int x[VMAX + 5];

int gcd(int a,int b){
	if(!b){
		return a;
	}
	return gcd(b,a % b);
}

int ans = 1e9;

int main(){
	
	scanf("%d",&n);
	
	int g = 0;
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&x[i]);
		g = gcd(g,x[i]);
	}
	
	for(int i = 1;i <= n;i++){
		cnt[x[i] / g]++;
	}	
	e[0] = e[1] = 1;
	
	ans = n;
	
	for(int i = 2;i <= VMAX;i++){
		if(!e[i]){
			for(int j = i;j <= VMAX;j += i){
				e[j] = 1;
				fr[i] += cnt[j];
			}
			
			if(fr[i] != n){
				ans = min(ans,n - fr[i]);
			}
		}
	}
	
	printf("%d",(ans == n ? -1 : ans));
	
	return 0;
}