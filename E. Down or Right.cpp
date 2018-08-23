#include <iostream>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 500;

int n;
char moves[2 * NMAX + 5];
int num_q = 0;
bool ask_query(int r1,int c1,int r2,int c2){
	if((!(1 <= r1 && r1 <= n)) || (!(1 <= r2 && r2 <= n))|| (!(1 <= c1 && c1 <= n)) || (!(1 <= c2 && c2 <= n))){
		return 0;
	}
	num_q++;
	if(num_q > 4 * n){
		throw runtime_error("too many queries");
	}
	if(r2 - r1 + c2 - c1 < n - 1){
		throw runtime_error("not long enough");
	}
	if(r1 > r2 || c1 > c2){
		throw runtime_error("comparator fails");
	}
	cout << "? " << r1 << " " << c1 << " " << r2 << " " << c2 << endl;
	string re;
	cin >> re;
	if(re[0] == 'B' || re[0] == 'b'){
		assert(false);
	}
	
	if(re[0] == 'Y' || re[0] == 'y'){
		return 1;
	}
	
	if(re[0] == 'N' || re[0] == 'n'){
		return 0;
	}
	
	throw runtime_error("message is actually " + re);
}

int main(){
	
	cin >> n;
	int xs = 1,ys = 1;
	
	string movess;
	
	while(xs + ys < n + 1){
		if(ask_query(xs + 1,ys,n,n)){
			movess += 'D';
			xs++;
		}
		else{
			movess += 'R';
			ys++;
		}
	}
	
	int xf = n,yf = n;
	
	string movesf;
	
	while(xf + yf > n + 1){
		if(ask_query(1,1,xf,yf - 1)){
			movesf += 'R';
			yf--;
		}
		else{
			movesf += 'D';
			xf--;
		}
	}
	
	reverse(movesf.begin(),movesf.end());
	
	cout << "! " << movess + movesf << endl;
	
	return 0;
}