#include <iostream>
#include <algorithm>

using namespace std;

int T;

int fr[8];
int D[100005];
bool was[1 << 9];

int gcd(int a,int b){
	if(!b){
		return a;
	}
	return gcd(b,a % b);
}

int main(){
	
	for(int i = 1;i <= 100000;i++){
		for(int j = i;j <= 100000;j += i){
			D[j]++;
		}
	}
	
	cin >> T;
	
	while(T--){
		int A,B,C;
		cin >> A >> B >> C;
		long long ans = 0;
		fr[7] = D[gcd(gcd(A,B),C)];
		fr[6] = D[gcd(B,C)] - fr[7];
		fr[5] = D[gcd(A,C)] - fr[7];
		fr[3] = D[gcd(A,B)] - fr[7];
		fr[4] = D[C] - fr[5] - fr[6] - fr[7];
		fr[2] = D[B] - fr[3] - fr[6] - fr[7];
		fr[1] = D[A] - fr[3] - fr[5] - fr[7];
		for(int maskA = 1;maskA < 8;maskA += 2){
			for(int maskB = 2;maskB < 8;maskB = (2 | (maskB + 1))){
				for(int maskC = 4;maskC < 8;maskC++){
		
					int minM = min(min(maskA,maskB),maskC);
					int maxM = max(max(maskA,maskB),maskC);
					int midM = maskA + maskB + maskC - minM - maxM;
					int bigM = minM + 8 * midM + 64 * maxM;
					if(was[bigM]){
						continue;
					}
					was[bigM] = 1;
		
					long long tmp = 1;
					tmp *= fr[maskA];
					
					if(maskB == maskA){
						tmp = tmp * (fr[maskB] + 1) / 2;
					}
					else{
						tmp = tmp * fr[maskB];
					}
					
					if(maskC == maskA && maskC == maskB){
						tmp = tmp * (fr[maskC] + 2) / 3; 
					}
					else if(maskC == maskA || maskC == maskB){
						tmp = tmp * (fr[maskC] + 1) / 2;
					}
					else{
						tmp = tmp * fr[maskC];
					}
					ans += tmp;
				}
			}
		}
		
		for(int maskA = 1;maskA < 8;maskA += 2){
			for(int maskB = 2;maskB < 8;maskB = (2 | (maskB + 1))){
				for(int maskC = 4;maskC < 8;maskC++){
					
					int minM = min(min(maskA,maskB),maskC);
					int maxM = max(max(maskA,maskB),maskC);
					int midM = maskA + maskB + maskC - minM - maxM;
					int bigM = minM + 8 * midM + 64 * maxM;

					was[bigM] = 0;
				}
			}
		}

		cout << ans << "\n";
	}
	
	
	return 0;
}