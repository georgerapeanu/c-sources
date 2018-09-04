#include <cstdio>

using namespace std;

FILE *f = stdin;
FILE *g = stdout;

const int NMAX = 1e6;
const int MOD = 1e9 + 7;
const int cealing = 10;

int n,k;
int v[NMAX + 5];
int left[NMAX + 5];
int right[NMAX + 5];
int st[NMAX + 5],len;

int progresie(int first,int delta,int num){
	return (1LL * first * num + ((1LL * delta * ((1LL * num * (num - 1) / 2) % MOD)) % MOD)) % MOD;
}

int main(){
	
	fscanf(f,"%d %d",&n,&k);
	
	for(int i = 1;i <= n;i++){
		fscanf(f,"%d",&v[i]);
	}
	
	for(int i = 1;i <= n;i++){
		while(len && v[st[len]] <= v[i]){
			len--;
		}
		left[i] = st[len];
		st[++len] = i;
	}
	
	len = 0;
	st[0] = n + 1;
	
	for(int i = n;i;i--){
		while(len && v[st[len]] < v[i]){
			len--;
		}
		right[i] = st[len];
		st[++len] = i;
	}
	
	int ans = 0;
	
	for(int i = 1;i <= n;i++){
		int tmp_ans = MOD - 1;
		
		///solving part till intersection with left
		int steps = (i - left[i] - 1) / (k - 1) + 1;
		tmp_ans = (tmp_ans + progresie(1,k - 1,steps)) % MOD;
		tmp_ans = (tmp_ans + 1LL * (i - left[i]) * (cealing - steps)) % MOD;
		
		
		
		///correcting intersection with right
		int step_with_right = (right[i] - i - 1) / (k - 1) + 1;
		int where_intersection = right[i] - (k - 1) * step_with_right;
		int first_elem = i - where_intersection + 1;
		int steps_left_right = (right[i] - left[i] - 1) / (k - 1) + 1;
		
		tmp_ans = (tmp_ans + MOD - progresie(first_elem,k - 1,steps_left_right - step_with_right)) % MOD;
		tmp_ans = (tmp_ans + MOD - (1LL * (i - left[i]) * (cealing - steps_left_right) % MOD)) % MOD;
		
		ans = (1LL * v[i] * tmp_ans + ans) % MOD;		
	}
	
	fprintf(g,"%d",ans);
	
	return 0;
}