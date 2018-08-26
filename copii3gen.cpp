#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

FILE *g = fopen("copii3.in","w");

int NMAX = 3000;
int QMAX = 300;

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
		else if(tmp == "QMAX"){
			string a = argv[++i];
			QMAX = parse(a);
		}
		else{
			throw runtime_error("invalid arguments");
		}
	}

	srand(time(NULL));


	int n = 0;
	int q = 0;

	n = rand() % NMAX + 1;
	q = rand() % QMAX;
	
	fprintf(g,"%d %d\n",n,q);

	for(int i = 1;i <= n;i++){
		fprintf(g,"%d",rand() & 1);
	}
	fprintf(g,"\n");
	while(q--){
		int st = rand() % n + 1,dr = rand() % n + 1;
		if(st > dr){
			swap(st,dr);
		}
		fprintf(g,"%d %d\n",st,dr);
	}


	return 0;
}