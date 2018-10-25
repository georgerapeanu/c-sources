#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("logs.in","r");
FILE *g = fopen("logs.out","w");

const int NMAX = 15e3;
const int MMAX = 15e2;
char C[MMAX + 5];

int heights[MMAX + 5];
int ordered[MMAX + 5];
int tmp[MMAX + 5];

int n,m;

int main(){
	
	fscanf(f,"%d %d\n",&n,&m);
	
	for(int i = 1;i <= m;i++){
		ordered[i] = i;
	}
	
	int ans = 0;
	
	for(int i = 1;i <= n;i++){
		fgets(C + 1,MMAX + 5,f);
		
		int cnt = 0;
		
		for(int i = 1;i <= m;i++){
			heights[i]++;
			if(C[i] == '0'){
				cnt ++;
				heights[i] = 0;
			}
			tmp[i] = ordered[i];
		}
		
		int be = 0;
		
		for(int i = 1;i <= m;i++){
			if(C[tmp[i]] == '0'){
				ordered[++be] = tmp[i];
			}
			else{
				ordered[++cnt] = tmp[i];
				ans = max(heights[ordered[cnt]] * (m - cnt + 1),ans);
			}
		}
	}
	
	fprintf(g,"%d",ans);
	
	fclose(f);
	fclose(g);
	
	return 0;
}