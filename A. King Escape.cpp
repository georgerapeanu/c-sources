#include <iostream>

using namespace std;

int n;
pair<int,int> queen;
pair<int,int> king;
pair<int,int> target;

int zona(pair<int,int> a,pair<int,int> b){
	b.first -= a.first;
	b.second -= a.second;
	
	if(b.first < 0){
		if(b.second < 0){
			return 1;
		}
		
		else{
			return 2;
		}
	}
	
	else{
		if(b.second < 0){
			return 3;
		}
		
		else{
			return 4;
		}
	}
}

int main(){
	
	cin >> n;
	cin >> queen.first >> queen.second;
	cin >> king.first >> king.second;
	cin >> target.first >> target.second;
	
	cout << (zona(queen,king) == zona(queen,target) ? "YES":"NO");
	
	return 0;
}