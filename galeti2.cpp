#include <cstdio>

using namespace std;

FILE *f = fopen("galeti2.in","r");
FILE *g = fopen("galeti2.out","w");

int n;
long long e;

int main(){
	
	fscanf(f,"%d %lld",&n,&e);
	
	for(int i = 2;i <= n;i++){
		if(1LL * i * (i - 1) / 2 + (n - i) >= e){
			long long elem = e - 1LL * (i - 2) * (i - 1) / 2 - (n - i);
			for(int j = i - 1;j > elem;j--){
				fprintf(g,"%d %d\n",j,j - 1);
			}
			
			fprintf(g,"%d %d\n",i,elem);
			
			for(int i = elem;i > 1;i--){
				fprintf(g,"%d %d\n",i,i - 1);
			}
			
			for(int j = i + 1;j <= n;j++){
				fprintf(g,"%d 1\n",j);
			}
			
			return 0;
		}
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}