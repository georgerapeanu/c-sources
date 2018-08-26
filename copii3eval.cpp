#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

FILE *f = fopen("copii3.in","r");
FILE *f1 = fopen("copii3.ok","r");
FILE *f2 = fopen("copii3.out","r");

const int NMAX = 30;
const int QMAX = 100;

int main(){
	
	srand(time(NULL));

	int n,q;

	fscanf(f,"%d %d\n",&n,&q);

	for(int i = 1;i <= q;i++){
		long long a,b;
		fscanf(f1,"%lld",&a);
		fscanf(f2,"%lld",&b);
		if(a != b){
			printf("WA on row %d",i);
			while(1);
		}
	}

	printf("OK\n");

	return 0;
}