#include <cstdio>

using namespace std;

FILE * f = fopen("nop.in","r");
FILE * g = fopen("nop.out","w");

const int LGMAX = 25;
const int n = LGMAX + 4;
const int m = 2 * LGMAX + 4;

char pattern[n][m];

int main(){

	for(int i = 0;i < n;i++){
		for(int j = 0;j < m - 1;j++){
			pattern[i][j] = '0';
		}
		pattern[i][m - 1] = '\0';
	}
	
	pattern[0][0] = '1';
	
	for(int bit = 0;bit <= LGMAX;bit++){
		pattern[bit][2 * bit + 1] = '1';
		pattern[bit + 1][2 * bit + 1] = '1';
		pattern[bit][2 * bit + 2] = '1';
		pattern[bit + 1][2 * bit + 2] = '1';
		for(int i = bit;i < n - 2;i++){
			pattern[i][2 * bit + 1] = '1';
		}
	}
	
	for(int j = 0;j < m - 1;j++){
		pattern[n - 1][j] = '1';
	}

	int q;
	
	fscanf(f,"%d",&q);
	
	while(q--){
		int c;
		fscanf(f,"%d",&c);
		for(int bit = LGMAX;bit >= 0;bit--){
			pattern[n - 2][2 * bit + 1] = '0' + ((c >> bit) & 1);
		}
		
		fprintf(g,"%d %d\n",n,m - 1);
		
		for(int i = 0;i < n;i++){
			fputs(pattern[i],g);
			fputc('\n',g);
		}			
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}