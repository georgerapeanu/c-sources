#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;
int n,q;
int a[200005];

int main(){
	
	freopen("in","r",stdin);
	freopen("ok","w",stdout);
	
	scanf("%d %d",&n,&q);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
	}
		
	while(q--){
		int t,l,r,x;
		
		scanf("%d %d %d %d",&t,&l,&r,&x);
		l++;
		r++;
		
		if(t == 0){
			for(int i = l; i <= r;i++){
				a[i] += x;
			}
		}
		
		else if(t == 1){
			for(int i = l; i <= r;i++){
				a[i] /= x;
			}
		}
		
		else{
			int ans = 0;
			for(int i = l; i <= r;i++){
				ans = max(ans,a[i]);
			}
			printf("%d\n",ans);
		}
	}
	
	return 0;
}