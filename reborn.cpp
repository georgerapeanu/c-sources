#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

FILE *f = fopen("reborn.in","r");
FILE *g = fopen("reborn.out","w");

const int NMAX = 2e5;
const int LGMAX = 18;

int n,m,q;
int seg_take[LGMAX + 1][NMAX + 5];
vector<int> event[NMAX + 5];

int main(){
	
	fscanf(f,"%d %d %d",&n,&m,&q);
	for(int i = 1;i <= m;i++){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		event[x].push_back(y);
	}
	
	for(int i = 1;i <= n;i++){
		seg_take[0][i] = max(seg_take[0][i - 1],i);
		for(auto it:event[i]){
			seg_take[0][i] = max(seg_take[0][i],it);
		}
	}
	
	for(int i = 1;i <= LGMAX;i++){
		for(int j = 1;j <= n;j++){
			seg_take[i][j] = seg_take[i - 1][seg_take[i - 1][j]];
		}
	}
	
	while(q--){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		if(x == y){
			fprintf(g,"0\n");
		}
		else{
			if(x > y){
				swap(x,y);
			}
			
			int ans = 0;
			
			for(int i = LGMAX;i >= 0;i--){
				if(seg_take[i][x] < y){
					x = seg_take[i][x];
					ans ^= 1 << i;
				}
			}
			
			if(seg_take[0][x] < y){
				fprintf(g,"-1\n");
			}
			else{
				fprintf(g,"%d\n",ans + 1);
			}
		}
	}
	
	return 0;
}