#include <cstdio>

using namespace std;

int main(){
	
	int z;
	
	scanf("%d",&z);
	
	while(z--){
		int n;
		scanf("%d",&n);
		fputc((n & 1) ? 'B':'A',stdout);
		fputc('\n',stdout);
	}
	
	return 0;
}