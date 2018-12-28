#include <cmath>
#include <cstdio>

using namespace std;

int main(){
	
	int z;
	
	scanf("%d",&z);
		
	while(z--){
			int x,y,z,r,a,b,c,d;
		scanf("%d %d %d %d %d %d %d %d",&x,&y,&z,&r,&a,&b,&c,&d);
		printf("%.10f\n",(acos(-1) * r) * r);		
	}

	return 0;
}