#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

FILE *f = fopen("minesweeper.in","r");
FILE *g = fopen("minesweeper.out","w");

///0-indexed
class GaussSolver{
	
private:
	
	const double EPS = 1e-10;
	int n;
	vector<double> solutions;
	vector< vector<double> > eq;
	vector<bool> free_elem;
	
public:

	GaussSolver(int n){
		this->n = n;
		this->solutions = vector<double>(n,0);
		this->eq = vector< vector<double> >();
		this->free_elem = vector<bool>(n,true);
	}
	
	void add(vector<double> &v){
		if((int)v.size() != n + 1){
			throw runtime_error("equation not valid");
		}		
		eq.push_back(v);
	}
	
	bool process(){
		int i = 0,j = 0;
		while(i < (int)eq.size() && j < n){
			
			bool found = false;
			
			for(int k = i;k < (int)eq.size();k++){
				if(abs(eq[k][j]) > EPS){
					swap(eq[k],eq[i]);
					found = true;
					
					double val = eq[i][j];
					for(auto &it:eq[i]){
						it /= val;
					}
					
					break;
				}					
			}
			
			if(!found){
				j++;
				continue;
			}
			
			for(int k = 0;k < (int)eq.size();k++){
				if(k == i){
					continue;
				}
				
				for(int l = 0;l <= n;l++){
					if(l != j){
						eq[k][l] -= eq[k][j] * eq[i][l];
					}
				}
				eq[k][j] = 0;
			}
			
			i++;
			j++;
		}
		
		for(int i = (int)eq.size() - 1;i >= 0;i--){
			for(int j = 0;j <= n;j++){
				if(abs(eq[i][j]) < EPS){
					continue;
				}
				
				if(j == n){
					return false;
				}
				
				if(abs(eq[i][j]) > EPS){
					solutions[j] = eq[i][n];
					for(int l = n - 1;l > i;l--){
						solutions[j] -= solutions[l] * eq[i][l];
					}
					free_elem[j] = false;
					break;
				}
			}
		}
		return true;
	}
	
	double get_sol(int pos){
		return solutions[pos];
	}
	
	int num_free(){
		int ans = 0;
		for(auto it:free_elem){
			ans += (it == true);
		}
		return ans;
	}
	
	bool is_free(int pos){
		return free_elem[pos];
	}
	
	void afis(){
		for(auto it:eq){
			for(auto it2:it){
				printf("%.6f ",it2);
			}
			printf("\n");
		}
		printf("\n");
	}
};

int n,m;

int main(){
	
	fscanf(f,"%d %d",&n,&m);
	
	n *= m;
	
	GaussSolver stuff((n + 1) * (n + 1));
	
	for(int a = 0;a <= n;a++){
		for(int b = 0;b <= n - a;b++){
			int c = n - a - b;
			vector<double> eq((n + 1) * (n + 1) + 1,0);
			eq[(n + 1) * a + b] = -1;
			
			if(b == n){
				stuff.add(eq);
				continue;
			}
			
			if(a){
				eq[(n + 1) * (a - 1) + b + 1] = ((double)a) / n;
			}
			
			if(b){
				eq[(n + 1) * (a) + b - 1] = ((double)b) / n;
			}
			
			if(c){
				eq[(n + 1) * (a + 1) + b] = ((double)c) / n;
			}
			
			eq[n] = 0;
			
			eq[(n + 1) * (n + 1)] = -1;
			stuff.add(eq);
		}
	}
	
	stuff.process();
	
	fprintf(g,"%.8f",stuff.get_sol(0));
	
	fclose(f);
	fclose(g);
	
	return 0;
}