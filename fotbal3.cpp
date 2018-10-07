#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("fotbal3.in","r");
FILE *g = fopen("fotbal3.out","w");

const int NMAX = 1e5;
const int VMAX = 3e5;

int n;
int v[NMAX + 5];
int l_min[NMAX + 5];
int r_min[NMAX + 5];
int l_max[NMAX + 5];
int r_max[NMAX + 5];
int stack_min[NMAX + 5],len_min;
int stack_max[NMAX + 5],len_max;
int pos[VMAX + 5];

int main(){
	
	fscanf(f,"%d",&n);
	
	for(int i = 1;i <= n;i++){
		fscanf(f,"%d",&v[i]);
		pos[v[i]] = i;
	}
	
	stack_min[len_min = 1] = 0;
	stack_max[len_max = 1] = 0;
	
	for(int i = 1;i <= n;i++){
		while(len_min > 1 && v[stack_min[len_min]] > v[i]){
			r_min[stack_min[len_min--]] = i;
		}
		
		while(len_max > 1 && v[stack_max[len_max]] < v[i]){
			r_max[stack_max[len_max--]] = i;
		}
		
		l_min[i] = stack_min[len_min];
		l_max[i] = stack_max[len_max];
		
		stack_min[++len_min] = i;
		stack_max[++len_max] = i;
	}
	
	///stack flush

	while(len_min > 1){
		r_min[stack_min[len_min--]] = n + 1;
	}
	
	while(len_max > 1){
		r_max[stack_max[len_max--]] = n + 1;
	}
	
	long long ans = 0;
	
	for(int i = 1;i <= VMAX;i++){
		if(!pos[i]){
			continue;
		}
		
		for(int j = i;j <= VMAX;j += i){
			if(!pos[j]){
				continue;
			}
			int a = pos[i];
			int b = pos[j];
			
			if(a <= b){
				if(l_max[b] <= a && r_min[a] >= b){
					ans += 1LL * (a - max(l_min[a],l_max[b])) * (min(r_min[a],r_max[b]) - b);
				}
			}
			else{
				if(l_min[a] <= b && r_max[b] >= a){
					ans += 1LL * (b - max(l_min[a],l_max[b])) * (min(r_min[a],r_max[b]) - a);
				}
			}
		}
	}
	
	fprintf(g,"%lld",ans);
	
	fclose(f);
	fclose(g);
	
	return 0;
}