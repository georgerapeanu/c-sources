#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int main(){
	int x,y,z,t1,t2,t3;
	
	cin >> x >> y >> z >> t1 >> t2 >> t3;
	
	long long stairs = 1LL * abs(x - y) * t1;
	long long elev = 1LL * abs(z - x) * t2 + t3 * 3LL + abs(y - x) * t2;
	
	if(stairs < elev){
		cout << "NO";
	}
	else{
		cout << "YES";
	}
	
	return 0;
}