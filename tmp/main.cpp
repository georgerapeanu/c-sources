#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
   
	int b = 60;
	int vmax = 7000;
	int ans = 0;
	
	for(int i = b;i <= vmax;i++){
		ans += (vmax / i);
	}
	
	cout << ans;
	
    return 0;
}