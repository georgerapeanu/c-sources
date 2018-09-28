#include <cstdio>

using namespace std;

FILE *f = fopen("diferente.in","r");
FILE *g = fopen("diferente.out","w");

const int NMAX = 1e3;

int n,k;
char ans[NMAX + 5][NMAX + 5];

int diag_start = 1;

int main(){
	
	fscanf(f,"%d %d",&n,&k);

	if(n % 2 == 1 && k % 2 == 1){
		fprintf(g,"impossible");
		return 0;
	}
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			ans[i][j] = '0';
		}
	}
		
	while(k > 0){
		
		for(int i = diag_start,j = 1;j <= n;i = i % n + 1,j++){
			ans[i][j] = '1';
		}
		
		diag_start += 2;
		k -= 2;
	}
	
	if(k != 0){
		for(int i = 2;i <= n;i += 2){
			ans[i][i] = '0';
		}
	}
	
	for(int i = 1;i <= n;i++){
		fputs(ans[i] + 1,g);
		fprintf(g,"\n");
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}