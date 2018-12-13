#include <iostream>

using namespace std;

int ask(int pos){
	cout << pos << endl;
	string ans;
	cin >> ans;
	return (ans == "Vacant" ? -1 : (ans == "Male" ? 0:1));
}

int main(){
	int n;
	
	cin >> n;
	
	int fst = ask(0);
	
	if(fst == -1){
		return 0;
	}
	
	int st = 0,dr = n - 1;
	
	while(dr - st > 1){
		int mid = (st + dr) / 2;
		int tmp = ask(mid);
		
		if(tmp == -1){
			return 0;
		}
		
		if(tmp == (fst ^ (mid & 1))){
			st = mid;
		}			
		else{
			dr = mid;
		}
	}
	
	ask(dr);
	
	
	return 0;
}