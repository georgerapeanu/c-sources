#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

int T;
int fr[1000005];
int fr2[1000005];
int X = -1;
int Y;
int mVAL = 0;

void Try(int N,int M,int X,int Y){
	
	///cout << N << " " << M << " " << X << " " << Y << "\n";
	
	if(X < 1 || X > N){
		return ;
	}
	
	if(Y < 1 || Y > M){
		return ;
	}
	
	memset(fr2,0,sizeof(fr2));
	
	for(int i = 1;i <= N;i++){
		for(int j = 1;j <= M;j++){
			fr2[abs(i - X) + abs(j - Y)]++;
		}
	}
	
	for(int i = 0;i <= (1e6);i++){
		if(fr[i] != fr2[i]){
			return ;
		}
	}
	
	cout << N << " " << M << "\n" << X << " " << Y << "\n";
	
	exit(0);
}

int main(){
	
	cin >> T;
	
	for(int i = 1;i <= T;i++){
		int x;
		cin >> x;
		fr[x]++;
		mVAL = max(mVAL,x);
	}
	
	X = -1;
	
	if(fr[0] + 3 != fr[1]){
		X = 1;
	}
	
	else{
		for(int i = 1;i <= (1e6);i++){
			if(fr[i] + 4 != fr[i + 1]){
				X = i + 1;
				break;
			}
		}
	}
	
	for(int i = 1;i <= T;i++){
		if(T % i == 0){
			int tmp = max(X - 1,i - X);
			int Y = mVAL - tmp;
			Try(i,T / i,X,Y);
			Y = tmp + T / i - mVAL;
			Try(i,T / i,X,Y);
		}
	}
	
	cout << -1;
	
	return 0;
}