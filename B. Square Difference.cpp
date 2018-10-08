#include <iostream>

using namespace std;

string prime(long long a){
	for(long long i = 2;i * i <= a;i++){
		if(a % i == 0){
			return "NO";
		}
	}
	return "YES";
}

int main(){
	
	int t;
	long long a,b;
	
	cin >> t;
	
	while(t--){
		cin >> a >> b;
		
		if(a != b + 1){
			cout << "NO\n";
		}
		
		else{
			cout << prime(a + b) << "\n";
		}
	}
	
	return 0;
}

