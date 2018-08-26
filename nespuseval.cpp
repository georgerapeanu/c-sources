#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

FILE *f1 = fopen("nespus.ok","r");
FILE *f2 = fopen("nespus.out","r");

int main(){

	long long a,b;
	fscanf(f1,"%lld",&a);
	fscanf(f2,"%lld",&b);
	if(a != b){
		printf("WA on row");
		while(1);
	}

	printf("OK\n");

	return 0;
}