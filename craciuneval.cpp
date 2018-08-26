#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

FILE *f1 = fopen("craciun.ok","r");
FILE *f2 = fopen("craciun.out","r");

int main(){
	

	double a,b;
	fscanf(f1,"%lf",&a);
	fscanf(f2,"%lf",&b);
	if(abs(a - b) > 1e-4){
		printf("WA");
		while(1);
	}

	printf("OK\n");

	return 0;
}