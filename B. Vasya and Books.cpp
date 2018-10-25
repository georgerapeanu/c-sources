#include <cstdio>

using namespace std;

int n;
int a[int(2e5) + 5];
int b[int(2e5) + 5];
int poz[int(2e5) + 5];
int ans[int(2e5) + 5];

int main(){
	
	scanf("%d",&n);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		poz[a[i]] = i;
	}
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&b[i]);
	}
	
	int top = 1;
	
	for(int i = 1;i <= n;i++){
		while(top <= poz[b[i]]){
			top++;
			ans[i]++;
		}
		printf("%d ",ans[i]);
	}
	
	
	return 0;
}