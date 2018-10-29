#include <cstdio>

using namespace std;

FILE *g = fopen("fenrir.out","w");

int main(){
	
	fprintf(g,"99\n");
	
	for(int i = 1;i <= 11;i++){
		for(int j = 1;j <= 9;j++){
			fprintf(g,"%d %d\n",2 * i - 1 - (i == 11),2 * j);
		}
	}
	
	fclose(g);
	
	return 0;
}