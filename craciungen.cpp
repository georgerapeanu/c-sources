#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

FILE *g = fopen("craciun.in","w");

int NMAX = 3000;
int WMAX = 3000;

int parse(string &a){
	int ans = 0;
	for(auto it:a){
		ans = ans * 10 + it - '0';
	}
	return ans;
}

int main(int argc,char **argv){

	for(int i = 1;i < argc;i++){
		string tmp = argv[i];
		if(tmp == "NMAX"){
			string a = argv[++i];
			NMAX = parse(a);
		}
		else if(tmp == "WMAX"){
			string a = argv[++i];
			WMAX = parse(a);
		}
		else{
			throw runtime_error("invalid arguments");
		}
	}

	srand(time(NULL));


	int n = 0;

	while(!n){
		n = rand() % NMAX;
	}

	fprintf(g,"%d\n",n);

	for(int i = 1;i <= n;i++){
		fprintf(g,"%d ",rand() % WMAX);
	}

	fprintf(g,"\n");
	
	for(int i = 1;i < n;i++){
		fprintf(g,"%d ",rand() % i + 1);
	}

	return 0;
}