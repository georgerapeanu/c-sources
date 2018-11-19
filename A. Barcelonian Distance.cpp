#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

int A,B,C;
int X1,X2,Y1,Y2;

long double dist(long double a,long double b,long double c,long double d){
	return sqrt((a - c) * (a - c) + (b - d) * (b - d));
}

int main(){
	
	cin >> A >> B >> C;
	cin >> X1 >> Y1 >> X2 >> Y2;
	
	long double best = (long double)abs(X1 - X2) + (long double)abs(Y1 - Y2);
	
	if(B == 0 || A == 0){
		cout << fixed << setprecision(10) << best;
		return 0;
	}
	
	long double sameX1 = (-C - ((long double)A) * X1) / B;
	long double sameX2 = (-C - ((long double)A) * X2) / B;
	long double sameY1 = (-C - ((long double)B) * Y1) / A;
	long double sameY2 = (-C - ((long double)B) * Y2) / A;
	
	best = min(best,abs(Y1 - sameX1) + dist(X1,sameX1,X2,sameX2) + abs(Y2 - sameX2));
	best = min(best,abs(Y1 - sameX1) + dist(X1,sameX1,sameY2,Y2) + abs(X2 - sameY2));
	best = min(best,abs(X1 - sameY1) + dist(sameY1,Y1,X2,sameX2) + abs(Y2 - sameX2));
	best = min(best,abs(X1 - sameY1) + dist(sameY1,Y1,sameY2,Y2) + abs(X2 - sameY2));
	
	cout << fixed << setprecision(10) << best;
	
	return 0;
}