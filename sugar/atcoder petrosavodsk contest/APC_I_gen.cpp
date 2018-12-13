#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int NMAX = 3e3;
const int QMAX = 3e3;
const int VMAX = 1e8 + 1;
const int XMAX = 1e8;

int main(){
	
	srand(time(NULL));
	
	FILE *g = fopen("in","w");
	
	int n = rand() % NMAX + 1;
	int q = rand() % QMAX + 1;
	
	fprintf(g,"%d %d\n",n,q);
	
	for(int i = 1;i <= n;i++){
		fprintf(g,"%d ",rand() % VMAX);
	}
	fprintf(g,"\n");
	
	for(int i = 1;i <= q;i++){
		int t,l,r,x;
		
		t = rand() % 3;
		l = rand() % n;
		r = rand() % n;
		x = rand() % XMAX + 1;
		
		if(l > r){
			swap(l,r);
		}
		
		fprintf(g,"%d %d %d %d\n",t,l,r,x);
	}
	
	fclose(g);
	
	return 0;
}