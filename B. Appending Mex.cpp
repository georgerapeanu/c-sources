#include <cstdio>
#include <algorithm>

using namespace std;

const int XMAX = 2e5;

int n;
int fr[XMAX + 5];

int main(){

	scanf("%d",&n);
	
	for(int i = 1;i <= n;i++){
		int x;
		fscanf(stdin,"%d",&x);
		x = min(x,XMAX);
		
		fr[x]++;
		
		if(x && (fr[x - 1] == 0)){
			fprintf(stdout,"%d\n",i);
			return 0;
		}
	}
	
	fprintf(stdout,"-1\n");

	return 0;
}