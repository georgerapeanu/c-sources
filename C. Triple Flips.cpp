#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const int inf = 1e9;

int n;
int dp[2][1 << 6];
pair<int,int> ant[NMAX + 5][1 << 6];
int v[NMAX + 20];

inline int get_conf(int st,int dr){
	int conf = 0;
	for(int i = 0;i <= dr - st;i++){
		conf |= ((st + i >= 1 ? v[st + i]:0) << i);
	}
	return conf;
}

inline int get_pos(int conf,int st,int dr,int pos){
	pos -= st;
	return (conf >> pos) & 1;
}

inline int slide(int conf,int st,int dr){
	conf >>= 1;
	conf |= ((v[dr + 1]) << (dr - st));
	return conf;
}

inline update(int &a,int b,int x,int y,int i,int j){
	if(a > b){
		a = b;
		ant[x][y] = {i,j};
	}
}

int main(){
	scanf("%d",&n);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&v[i]);
	}
	
	for(int i = 0;i < 2;i++){
		for(int j = 0;j < (1 << 6);j++){
			dp[i][j] = inf;
		}
	}
	
	dp[0][get_conf(-2,3)] = 0;
	
	for(int i = 0,l = 0;i < n + 3;i++,l ^= 1){
		for(int j = 0;j < (1 << 6);j++){
			if(dp[i][j] == inf){
				continue;
			}
			
			if(get_pos(j,i - 2,i + 3,0) == 0){
				int m1 = slide(j,i - 2,i - 3) ^ (0);
				int m2 = slide(j,i - 2,i - 3) ^ (21);
				int m3 = slide(j,i - 2,i - 3) ^ (14);
				int m4 = slide(j,i - 2,i - 3) ^ (27);
				update(dp[l ^ 1][m1],dp[l][j] + 1,i,m1,0,j);///000000
				update(dp[l ^ 1][m2],dp[l][j] + 1,i,m2,21,j);///010101
				update(dp[l ^ 1][m3],dp[l][j] + 1,i,m3,14,j);///001110
				update(dp[l ^ 1][m4],dp[l][j] + 1,i,m4,27,j);///011011
			}
			else{
				int m1 = slide(j,i - 2,i - 3) ^ (36);
				int m2 = slide(j,i - 2,i - 3) ^ (49);
				int m3 = slide(j,i - 2,i - 3) ^ (42);
				int m4 = slide(j,i - 2,i - 3) ^ (63);
				update(dp[l ^ 1][m1],dp[l][j] + 1,i,m1,36,j);///100100
				update(dp[l ^ 1][m2],dp[l][j] + 1,i,m2,49,j);///110001
				update(dp[l ^ 1][m3],dp[l][j] + 1,i,m3,42,j);///101010
				update(dp[l ^ 1][m4],dp[l][j] + 1,i,m4,63,j);///111111
			}
			dp[i][j] = inf;
		}
	}
	
	int ans = dp[(n + 3) % 2][0];
	int conf = 0;
	
	if(ans == inf){
		printf("NO\n");
		return 0;
	}
	
	printf("YES\n%d\n",ans);
	
	for(int i = n + 3;i;i--){
		int op = ant[i][conf].first;
		if(op == 0);
		else if(op == 21 && i-2 >0 && i + 2 <= n)printf("%d %d %d\n",i-2,i,i + 2);
		else if(op == 14 && i - 1 >0 && i + 1 <= n)printf("%d %d %d\n",i - 1,i,i + 1);
		else if(op == 27)printf("%d %d %d\n%d %d %d\n",i-2,i,i + 2,i-1,i,i + 1);
		else if(op == 36 && i-3 >0 && i + 3 <= n)printf("%d %d %d\n",i-3,i,i + 3);
		else if(op == 49 && i-3 >0 && i + 3 <= n)printf("%d %d %d\n%d %d %d\n",i - 1,i,i + 1,i - 3,i,i + 3);
		else if(op == 42 && i-3 >0 && i + 3 <= n)printf("%d %d %d\n%d %d %d\n",i-2,i,i + 2,i - 3,i,i + 3);
		else if(op == 63 && i-3 >0 && i + 3 <= n)printf("%d %d %d\n%d %d %d\n%d %d %d\n",i-2,i,i + 2,i-1,i,i + 1,i - 3,i,i + 3);
		conf = ant[i][conf].second;
	}
	
	return 0;
}

