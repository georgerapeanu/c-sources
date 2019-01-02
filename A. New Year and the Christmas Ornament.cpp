#include <cstdio>
#include <algorithm>

using namespace std;

int main(){
	int y,b,r;
	scanf("%d %d %d",&y,&b,&r);
	printf("%d",3 * min(min(r - 1,b),y + 1));
	
	return 0;
}