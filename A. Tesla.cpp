#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector < pair<int,pair<int,int> > > op;

int N,K;
int V[5][55];
int cnt_done;

void baga(){
	for(int i = 1;i <= N;i++){
		if(V[1][i] != 0 && V[1][i] == V[2][i]){
			V[2][i] = 0;
			op.push_back({V[1][i],{1,i}});
			cnt_done++;
		}
		if(V[4][i] != 0 && V[3][i] == V[4][i]){
			V[3][i] = 0;
			op.push_back({V[4][i],{4,i}});
			cnt_done++;
		}
	}
}

bool muta(){
	
	for(int i = 1;i <= N;i++){
		if(V[2][i] == 0){
			for(int j = i;j < N;j++){
				if(V[2][j + 1]){
					swap(V[2][j],V[2][j + 1]);
					op.push_back({V[2][j],{2,j}});
				}
			}
			
			if(V[3][N]){
				swap(V[2][N],V[3][N]);
				op.push_back({V[2][N],{2,N}});
			}
			
			for(int j = N;j > 1;j--){
				if(V[3][j - 1]){
					swap(V[3][j - 1],V[3][j]);
					op.push_back({V[3][j],{3,j}});
				}
			}
			
			if(V[2][1] && i != 1){
				swap(V[3][1],V[2][1]);
				op.push_back({V[3][1],{3,1}});
			}
			
			for(int j = 1;j < i - 1;j++){
				if(V[2][j + 1]){
					swap(V[2][j],V[2][j + 1]);
					op.push_back({V[2][j],{2,j}});
				}
			}
			
			return 1;
			
			break;
		}
		if(V[3][i] == 0){
			
			for(int j = i;j > 1;j--){
				if(V[3][j - 1]){
					swap(V[3][j - 1],V[3][j]);
					op.push_back({V[3][j],{3,j}});
				}
			}
			
			if(V[2][1]){
				swap(V[3][1],V[2][1]);
				op.push_back({V[3][1],{3,1}});
			}
			
			for(int j = 1;j < N;j++){
				if(V[2][j + 1]){
					swap(V[2][j],V[2][j + 1]);
					op.push_back({V[2][j],{2,j}});
				}
			}
			
			if(V[3][N] && i != N){
				swap(V[2][N],V[3][N]);
				op.push_back({V[2][N],{2,N}});
			}
			
			for(int j = N;j > i + 1;j--){
				if(V[3][j - 1]){
					swap(V[3][j],V[3][j - 1]);
					op.push_back({V[3][j],{3,j}});
				}
			}
			
			return 1;
			
			break;
		}
	}
	
	return 0;
	
}

int main(){
	
	cin >> N >> K;
	
	for(int i = 1;i <= 4;i++){
		for(int j = 1;j <= N;j++){
			cin >> V[i][j];
		}
	}
	
	baga();
	if(cnt_done < K && !muta()){
		cout << -1;
		return 0;
	}
	
	while(cnt_done < K){
		baga();
		muta();
	}
	
	cout << op.size() << "\n";
	
	for(auto it:op){
		cout << it.first << " " << it.second.first << " " << it.second.second << "\n";
	}
	
	return 0;
}