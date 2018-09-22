#include <cstdio>
#include <algorithm>
#include <vector>
 
using namespace std;
 
FILE *f = fopen("mezzaluna.in","r");
FILE *g = fopen("mezzaluna.out","w");
 
const int NMAX = 1e5;
const int XMAX = 2e3;
const int MOD = 1e9 + 7;
 
int n;
 
int cnt[XMAX + 5][XMAX + 5];
int how_many_right[XMAX + 5][XMAX + 5];
int how_many_up[XMAX + 5][XMAX + 5];
 
int max_aib[XMAX + 5][XMAX + 5];
int line_max[XMAX + 5];
int col_max[XMAX + 5];
int max_dp[XMAX + 5][XMAX + 5];
 
int add(int a,int b){
	a += b;
	if(a >= MOD){
		a -= MOD;
	}
	return a;
}
 
void u_max_aib(int x,int y,int val){
    for(int i = x;i <= XMAX;i += (-i) & i){
        for(int j = y;j;j -= (-j) & j){
            max_aib[i][j] = max(max_aib[i][j],val);
        }
    }
}
 
int q_max_aib(int x,int y){
    int ans = 0;
    for(int i = x;i;i -= (-i) & i){
        for(int j = y;j <= XMAX;j += (-j) & j){
            ans = max(ans,max_aib[i][j]);
        }
    }
     
    return ans;
}

int num_dp[XMAX + 5][XMAX + 5];
int num_stuff[XMAX + 5][XMAX + 5];
 
void num_u(int l,int c,int val){
	for(;c;c -= (-c) & c){
		num_stuff[l][c] = add(num_stuff[l][c],val);
	}
}

int num_q(int l,int c){
	if(l < 0){
		return 0;
	}
	
	if(l == 0){
		return 1;
	}
	int ans = 0;
	for(;c <= XMAX;c += (-c) & c){
		ans = add(ans,num_stuff[l][c]);
	}
	return ans;
}
 
const int LEN = 1 << 12;
int ind = LEN - 1;
char buff[LEN];

int i32(){
	int ans = 0;
	
	while(buff[ind] < '0' || buff[ind] > '9'){
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	
	while(!(buff[ind] < '0' || buff[ind] > '9')){
		ans = ans * 10 + buff[ind] - '0';
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	return ans;
}	

int main(){
     
    n = i32();
     
    for(int i = 1;i <= n;i++){
        int x,y;
        x = i32();
		y = i32();
        cnt[x][y]++;
    }
     
    for(int i = 1;i <= XMAX;i++){
        for(int j = XMAX;j;j--){
            how_many_right[i][j] = cnt[i][j] + how_many_right[i][j + 1];
            how_many_up[i][j] = cnt[i][j] + how_many_up[i - 1][j];
        }
    }
     
    int ans = 0;
     
    for(int i = 1;i <= XMAX;i++){
        for(int j = XMAX;j > i;j--){
             
            if(cnt[i][j]){
                max_dp[i][j] = max(max_dp[i][j],1 + q_max_aib(i - 1,j + 1));
                max_dp[i][j] = max(max_dp[i][j],1);
            }
             
            if(how_many_up[i][j] && line_max[i]){
                max_dp[i][j] = max(max_dp[i][j],line_max[i] + 1);
            }
             
            if(how_many_right[i][j] && col_max[j]){
                max_dp[i][j] = max(max_dp[i][j],col_max[j] + 1);
            }
 
            if(max_dp[i][j]){
                line_max[i] = max(line_max[i],max_dp[i][j]);            
                col_max[j] = max(col_max[j],max_dp[i][j]);
                u_max_aib(i,j,max_dp[i][j]);
				ans = max(ans,max_dp[i][j]);
			}
        }
    }
	
	int num_ans = 0;
	
	for(int i = 1;i <= XMAX;i++){
		for(int j = XMAX;j;j--){
			num_dp[i][j] = num_q(max_dp[i][j] - 1,j);
			num_u(max_dp[i][j],j,num_dp[i][j]);
			if(max_dp[i][j] == ans){
				num_ans = add(num_ans,num_dp[i][j]);
			}
		}
	}
	
	// for(int i = 1;i <= 4;i++){
		// for(int j = 1;j <= 4;j++){
			// printf("%d ",num_dp[i][j]);
		// }
		// printf("\n");
	// }
     
    fprintf(g,"%d %d",ans,num_ans);
     
    fclose(f);
    fclose(g);
 
    return 0;
}