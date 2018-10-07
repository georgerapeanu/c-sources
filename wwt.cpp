#include <cstdio>

using namespace std;

FILE *f = fopen("wwt.in","r");
FILE *g = fopen("wwt.out","w");

const int NMAX = 200;
const int KMAX = 10;
const int PWMAX = 60000;
const int MOD = 1e9 + 7;

int n,k;
int v[NMAX + 1];
int pw3[KMAX + 1];
int dp[NMAX + 1][PWMAX + 1][2];
int initial_test_label[NMAX + 5];

int add(int a,int b){
	a += b;
	if(a >= MOD){
		a -= MOD;
	}
	return a;
}

int get_pos(int conf,int pos){
	return (conf / pw3[pos]) % 3;
}

int main(){
	
	pw3[0] = 1;
	for(int i = 1;i <= KMAX;i++){
		pw3[i] = pw3[i - 1] * 3;
	}
	
	fscanf(f,"%d %d",&n,&k);
	
	bool initial_ok = 1;
	
	v[0] = -1;
	
	for(int i = 1;i <= n;i++){
		fscanf(f,"%d",&v[i]);
		v[i]--;
		
		if(v[i] == v[i - 1]){
			continue;
		}
		
		if(!initial_test_label[v[i]]){
			initial_test_label[v[i]] = initial_test_label[v[i - 1]] % 2 + 1;
		}
		
		else if(initial_test_label[v[i]] != (initial_test_label[v[i - 1]] % 2 + 1)){
			initial_ok = 0;
		}
	}
	
	dp[1][0][1] = 1;
	dp[1][pw3[v[1]]][0] = 1;
	dp[1][2 * pw3[v[1]]][0] = 1;
	for(int i = 1;i < n;i++){
		for(int conf = 0;conf < pw3[k];conf++){
			if(dp[i][conf][0] + dp[i][conf][1] == 0){
				continue;
			}
			
			if(get_pos(conf,v[i + 1]) == 0){///undecided
				dp[i + 1][conf][1] = add(dp[i + 1][conf][1],dp[i][conf][1]);
				dp[i + 1][conf + pw3[v[i + 1]]][0] = add(dp[i + 1][conf + pw3[v[i + 1]]][0],dp[i][conf][1]);
				
				if(get_pos(conf,v[i]) == 1){
					dp[i + 1][conf][1] = add(dp[i + 1][conf][1],dp[i][conf][0]);
					// printf("%d %d %d %d\n",i,conf,conf + 2 * pw3[v[i + 1]],dp[i][conf][0]);
					dp[i + 1][conf + 2 * pw3[v[i + 1]]][0] = add(dp[i + 1][conf + 2 * pw3[v[i + 1]]][0],dp[i][conf][0]);
				}
				
				else if(get_pos(conf,v[i]) == 2){
					dp[i + 1][conf + pw3[v[i + 1]]][0] = add(dp[i + 1][conf + pw3[v[i + 1]]][0],dp[i][conf][0]);
				}
			}
			
			else if(get_pos(conf,v[i + 1]) == 1){///against
				dp[i + 1][conf][0] = add(dp[i + 1][conf][0],dp[i][conf][1]);
				dp[i + 1][conf][1] = add(dp[i + 1][conf][1],dp[i][conf][1]);
				
				if(v[i] == v[i + 1]){
					dp[i + 1][conf][0] = add(dp[i + 1][conf][0],dp[i][conf][0]);
					dp[i + 1][conf][1] = add(dp[i + 1][conf][1],dp[i][conf][0]);
				}
				
				else if(get_pos(conf,v[i]) == 1){
					dp[i + 1][conf][1] = add(dp[i + 1][conf][1],dp[i][conf][0]);
				}
				
				else if(get_pos(conf,v[i]) == 2){
					dp[i + 1][conf][0] = add(dp[i + 1][conf][0],dp[i][conf][0]);
				}
			}
			
			else{///with
				dp[i + 1][conf][1] = add(dp[i + 1][conf][1],dp[i][conf][1]);
				
				if(v[i] == v[i + 1]){
					dp[i + 1][conf][0] = add(dp[i + 1][conf][0],dp[i][conf][0]);
				}
				
				else if(get_pos(conf,v[i]) == 1){
					dp[i + 1][conf][0] = add(dp[i + 1][conf][0],dp[i][conf][0]);
					dp[i + 1][conf][1] = add(dp[i + 1][conf][1],dp[i][conf][0]);
				}
			}
		}
	}
	
	int ans = MOD - initial_ok;
	// printf("\n\n\n\n%d %d\n",dp[4][16][0],dp[4][16][1]);
	for(int conf = 1;conf < pw3[k];conf++){
		ans = add(ans,dp[n][conf][1]);
		ans = add(ans,dp[n][conf][0]);
		// printf("%d %d %d\n",conf,dp[n][conf][0],dp[n][conf][1]);
	}
	
	fprintf(g,"%d",ans);
	
	return 0;
}