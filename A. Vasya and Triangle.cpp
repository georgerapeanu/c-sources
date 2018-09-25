#include <cstdio>
#include <cstdlib>

using namespace std;

int n,m,k;

int main(){
	
	scanf("%d %d %d",&n,&m,&k);
	
	for(int i = 1;1LL * i * i <= k;i++){
		if(k % i == 0){
			int x = k / i;
			int y = i;
			
			if((2 * n) % x == 0 && m % y == 0 && x > 1){
				printf("YES\n");
				printf("%d %d\n",0,0);
				printf("%d %d\n",2 * n / x,0);
				printf("%d %d\n",0,m / y);
				return 0;
			}
			
			if((2 * n) % y == 0 && m % x == 0 && y > 1){
				printf("YES\n");
				printf("%d %d\n",0,0);
				printf("%d %d\n",2 * n / y,0);
				printf("%d %d\n",0,m / x);
				return 0;
			}
			
			if(n % x == 0 && (2 * m) % y == 0 && y > 1){
				printf("YES\n");
				printf("%d %d\n",0,0);
				printf("%d %d\n",n / x,0);
				printf("%d %d\n",0,2 * m / y);
				return 0;
			}
			
			if(n % y == 0 && (2 * m) % x == 0 && x > 1){
				printf("YES\n");
				printf("%d %d\n",0,0);
				printf("%d %d\n",n / y,0);
				printf("%d %d\n",0,2 * m / x);
				return 0;
			}
		}
	}
	
	printf("NO");
	
	return 0;
}