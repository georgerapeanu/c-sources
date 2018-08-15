#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("loto.in","r");
FILE *g = fopen("loto.out","w");

vector<int> Sums;
int fst = -1,lst = -1;
int N,S;
int V[105];

int main(){
	
	fscanf(f,"%d %d",&N,&S);
	for(int i = 1;i <= N;i++){
		fscanf(f,"%d",&V[i]);
	}
	
	for(int i = 1;i <= N;i++){
		for(int j = i;j <= N;j++){
			for(int k = j;k <= N;k++){
				Sums.push_back(V[i] + V[j] + V[k]);
			}
		}
	}
	
	sort(Sums.begin(),Sums.end());
	int dr = (int)Sums.size() - 1;
	for(int st = 0;st <= dr;st++){
		while(Sums[st] + Sums[dr] > S && dr >= st){
			dr--;
		}
		if(st <= dr && Sums[st] + Sums[dr] == S){
			fst = Sums[st];
			lst = Sums[dr];
			break;
		}
	}
	
	if(fst == -1 && lst == -1){
		fprintf(g,"-1");
		goto done2;
	}
	
	for(int i = 1;i <= N;i++){
		for(int j = i;j <= N;j++){
			for(int k = j;k <= N;k++){
				if(V[i] + V[j] + V[k] == fst){
					fprintf(g,"%d %d %d ",V[i],V[j],V[k]);
					goto done1;
				}
			}
		}
	}
	done1:;
	for(int i = 1;i <= N;i++){
		for(int j = i;j <= N;j++){
			for(int k = j;k <= N;k++){
				if(V[i] + V[j] + V[k] == lst){
					fprintf(g,"%d %d %d ",V[i],V[j],V[k]);
					goto done2;
				}
			}
		}
	}
	done2:;
	
	fclose(f);
	fclose(g);

	return 0;
}