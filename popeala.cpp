#include <cstdio>
#include <iostream>

using namespace std;

FILE *f = fopen("popeala.in","r");
FILE *g = fopen("popeala.out","w");

const int TMAX = 2e4;
const int NMAX = 50;
const int SMAX = 50;

int t,n,s;

int points[TMAX + 5];
int prefix_sum[TMAX + 5];

char results[NMAX + 5][TMAX + 5];

int best_for[NMAX + 5][NMAX + 5];

int dp[TMAX + 5][SMAX + 5];

int nxt[NMAX + 5];
int ant[NMAX + 5];
int head;
int valid_from[TMAX + 5][NMAX + 5];


int main(){
	
	fscanf(f,"%d %d %d",&n,&t,&s);
	
	for(int i = 1;i <= t;i++){
		fscanf(f,"%d",&points[i]);
		prefix_sum[i] = prefix_sum[i - 1] + points[i];
	}
	
	fscanf(f,"\n");
	
	for(int i = 1;i <= n;i++){
		fgets(results[i] + 1,TMAX + 5,f);
	}
	
	for(int i = 1;i <= n;i++){
		valid_from[i][0] = 1;
		for(int j = 1;j <= t;j++){
			valid_from[i][j] = (results[i][j] == '1' ? valid_from[i][j - 1]:j + 1);
		}
	}

	for(int i = 1;i <= t;i++){
		dp[i][0] = -(1 << 30);
	}
		
	for(int j = 1;j <= s;j++){
		
		for(int i = 0;i < n;i++){
			nxt[i] = i + 1;
			ant[i + 1] = i;
			
		}
		head = n;
		
		for(int i = 1;i <= t;i++){
			for(int k = 1;k <= n;k++){
				if(valid_from[k][i] != valid_from[k][i - 1]){
					if(k != head){
						nxt[ant[k]] = nxt[k];
						ant[nxt[k]] = ant[k];
						nxt[head] = k;
						ant[k] = head;
						nxt[k] = 0;
						head = k;
					}
				}
			}
			
		}
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}