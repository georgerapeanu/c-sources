#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>

using namespace std;

FILE *f = fopen("routere.in","r");
FILE *g = fopen("routere.out","w");

const int NMAX = 1000;
const int MOD = 666013;

int add(int a,int b){
	a += b;
	if(a >= MOD){
		a -= MOD;
	}
	return a;
}

int mult(int a,int b){
	return 1LL * a * b % MOD;
}

int gcd(int a,int b){
	if(!b){
		return a;
	}
	return gcd(b,a % b);
}

int lcm(int a,int b){
	return a * b / gcd(a,b);
}

int n;
int comb[NMAX + 5][NMAX + 5];
int v[NMAX + 5];
int delta[NMAX + 5];
bool router[NMAX + 5];
int ans;

void baga(int r){
	memset(router,0,sizeof(router));
	
	int sum = 0;
	
	for(int i = 1;i <= n;i++){
		delta[i] = v[i] - v[i % n + 1];
		sum += v[i];
	}
	
	bool ok = 1;
	int routers = 0;
	
	for(int i = 1;i <= n;i++){
		ok &= (abs(delta[i]) <= 1);
		
		int a = i;
		
		while(delta[a] == -1 && ok){
			if(router[a] == 1){
				ok = 0;
				break;
			}
			routers++;
			delta[a]++;
			delta[(a + r - 1) % n + 1]--;
			router[a] = 1;
			a = (a + r - 1) % n + 1;
		}
	}
	
	int taken_paths = 0,ja = gcd(n,r);
	for(int i = 1;i <= n;i++){
		router[(i - 1) % ja + 1] |= router[i];
		ok &= (delta[i] == 0);
	}
	
	for(int i = 1;i <= ja;i++){
		taken_paths += router[i];
	}
	
	if(!ok){
		return ;
	}
	
	int el = (sum - r * routers) / n;
	int scad = lcm(n,r) / n;
	
	if(el < 0){
		return ;
	}
	
	else if(el == 0){
		ans = add(ans,1);
	}
	
	else if(el % scad == 0 && gcd(n,r) >= taken_paths){
		ans = add(ans,comb[gcd(n,r) - taken_paths][el / scad]);
	}
	
}

int main(){
	
	fscanf(f,"%d",&n);
	
	for(int i = 1;i <= n;i++){
		fscanf(f,"%d",&v[i]);
	}
	
	comb[0][0] = 1;
	
	for(int i = 1;i <= n;i++){
		comb[i][0] = 1;
		for(int j = 1;j <= i;j++){
			comb[i][j] = add(comb[i - 1][j - 1],comb[i - 1][j]);
		}
	}
	
	for(int i = 1;i < n;i++){
		baga(i);
	}
	
	fprintf(g,"%d\n",ans);
	
	fclose(f);
	fclose(g);
	
	return 0;
}