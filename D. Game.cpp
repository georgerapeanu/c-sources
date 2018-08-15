#include <cstdio>

using namespace std;

int N,R;
long double ans;
long double u;
int f[1 << 18];

int main(){
	scanf("%d %d",&N,&R);
	
	u = 1;
	
	for(int i = 1;i <= N;i++){
		u /= 2;
	}
	
	for(int i = 0;i < (1 << N);i++){
		int val;
		scanf("%d",&f[i]);
		ans += u * f[i];
	}
	
	printf("%.7f\n",(double)ans);
	
	while(R--){
		int x,y;
		scanf("%d %d",&x,&y);
		ans += u * (y - f[x]);
		f[x] = y;
		printf("%.7f\n",(double)ans);
	}
	
	return 0;
}