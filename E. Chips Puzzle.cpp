#include <iostream>
#include <vector>
#include <cassert>
#include <deque>
#define JUDGE 1

using namespace std;

int n,m;
deque<char> init[305][305];
deque<char> fin[305][305];

int sus[305][2];
int jos[305][2];

int up_demand[305];
int down_demand[305];

struct data{
	int a,b,c,d;
};
vector<data> ans;
void transfer(int stx,int sty,int fnx,int fny){
	ans.push_back({stx,sty,fnx,fny});
	assert(init[stx][sty].size());
	assert((stx != fnx || sty != fny) && (stx == fnx || sty == fny));
	init[fnx][fny].push_front(init[stx][sty].back());
	init[stx][sty].pop_back();
}

int main(){
	
	cin >> n >> m;
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			string a;
			cin >> a;
			for(auto it:a){
				init[i][j].push_back(it);
			}
		}
	}
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			string a;
			cin >> a;
			for(auto it:a){
				fin[i][j].push_back(it);
			}
		}
	}
	
	///divide
	
	for(int j = 1;j <= m;j++){
		int ind = 0;
		while(ind < (int)init[1][j].size() && init[1][j][ind] == '0'){
			ind++;
		}
		
		for(int k = (int)init[1][j].size() - 1;k >= ind;k--){
			if(init[1][j][k] == '0'){
				transfer(1,j,1,j % m + 1);
			}
			else{
				transfer(1,j,n,j);
			}
		}
		
		ind = 0;
		while(ind < (int)init[n][j].size() && init[n][j][ind] == '1'){
			ind++;
		}
		
		for(int k = (int)init[n][j].size() - 1;k >= ind;k--){
			if(init[n][j][k] == '1'){
				transfer(n,j,n,j % m + 1);
			}
			else{
				transfer(n,j,1,j);
			}
		}
	}
	
	for(int i = 2;i < n;i++){
		for(int j = 1;j <= m;j++){
			for(int k = (int)init[i][j].size() - 1;k >= 0;k--){
				if(init[i][j][k] == '0'){
					transfer(i,j,1,j);
				}
				else{
					transfer(i,j,n,j);
				}
			}
		}
	}
	
	if(!JUDGE){		
		cout << "divide\n";
		
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				if(init[i][j].size() == 0){
					cout << "null ";
				}
				else{
					string a;
					for(auto it:init[i][j]){
						a += it;
					}
					cout << a << " ";
				}
			}
			cout << "\n";
		}
	}
	
	///remake center

	for(int i = 2;i < n;i++){
		for(int j = 1;j <= m;j++){
			for(int k = (int)fin[i][j].size() - 1;k >= 0;k--){
				if(fin[i][j][k] == '1'){
						if(init[n][j].size()){
							transfer(n,j,i,j);
						}
						else{
							for(int l = 1;l <= m;l++){
								if(init[n][l].size()){
									transfer(n,l,n,j);
									break;
								}
							}
							transfer(n,j,i,j);
						}
				}
				else{
					if(init[1][j].size()){
						transfer(1,j,i,j);
					}
					else{
						for(int l = 1;l <= m;l++){
							if(init[1][l].size()){
								transfer(1,l,1,j);
								break;
							}
						}
						transfer(1,j,i,j);
					}
				}
			}
		}
	}
	
	if(!JUDGE){		
		cout << "remake center\n";
		
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				if(init[i][j].size() == 0){
					cout << "null ";
				}
				else{
					string a;
					for(auto it:init[i][j]){
						a += it;
					}
					cout << a << " ";
				}
			}
			cout << "\n";
		}
	}
	
	
	///prepare full remake
	
	for(int j = 1;j <= m;j++){
		for(auto it:fin[1][j]){
			sus[j][it - '0']++;
		}
		
		for(auto it:fin[n][j]){
			jos[j][it - '0']++;
		}
	}
	
	for(int j = 1;j <= m;j++){
		up_demand[j] = jos[j][0] + sus[j % m + 1][0];
		down_demand[j] = sus[j][1] + jos[j % m + 1][1];
	}
	
	for(int j = 1;j <= m;j++){
		for(int k = 1;k <= m;k++){
			if(k != j){
				while((int)init[1][j].size() < up_demand[j] && up_demand[k] < (int)init[1][k].size()){
					transfer(1,k,1,j);
				}
				
				while((int)init[n][j].size() < down_demand[j] && down_demand[k] < (int)init[n][k].size()){
					transfer(n,k,n,j);
				}
			}
		}
		
	}

	if(!JUDGE){		
		cout << "prepare full remake\n";
		
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				if(init[i][j].size() == 0){
					cout << "null ";
				}
				else{
					string a;
					for(auto it:init[i][j]){
						a += it;
					}
					cout << a << " ";
				}
			}
			cout << "\n";
		}
	}

	
	///full remake
	
	for(int j = 1;j <= m;j++){
		for(int k = (int)fin[1][j].size() - 1;k >= 0;k--){
			if(fin[1][j][k] == '0'){
				transfer(1,(j == 1 ? m : j - 1),1,j);
			}
			else{
				transfer(n,j,1,j);
			}
		}
		
		for(int k = (int)fin[n][j].size() - 1;k >= 0;k--){
			if(fin[n][j][k] == '1'){
				transfer(n,(j == 1 ? m : j - 1),n,j);
			}
			else{
				transfer(1,j,n,j);
			}
		}
	}
	
	if(!JUDGE){		
		cout << "full remake\n";
		
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= m;j++){
				if(init[i][j].size() == 0){
					cout << "null ";
				}
				else{
					string a;
					for(auto it:init[i][j]){
						a += it;
					}
					cout << a << " ";
				}
			}
			cout << "\n";
		}
	}
	
	cout << ans.size() << "\n";
	
	for(auto it:ans){
		cout << it.a << " " << it.b << " " << it.c << " " << it.d << "\n";
	}
	
	return 0;
}