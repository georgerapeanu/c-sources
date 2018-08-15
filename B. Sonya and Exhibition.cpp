#include <iostream>

using namespace std;

int N;

int main(){

	cin >> N;
	
	for(int i = 1;i <= N;i++){
		cout << (i % 2);
	}

	return 0;
}