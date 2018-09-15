#include <iostream>

using namespace std;

int n;
long long a[1<<10][1<<10];

void solve(int stx,int sty,int drx,int dry){
	if(stx == drx && sty == dry){
		a[stx][sty] = 1;
		return ;
	}
	
	int midx = (stx + drx) / 2;
	int midy = (sty + dry) / 2;
	
	solve(stx,sty,midx,midy);
	
	for(int i = midx + 1;i <= drx;i++){
		for(int j = 1;j <= midy;j++){
			a[i][j] = 2 * a[2 * midx - i][j];
		}
	}
	
	for(int i = 1;i <= midx;i++){
		for(int j = midy + 1;j <= dry;j++){
			a[i][j] = 3 * a[2 * 
		}
	}
}

int main(){
	
	cin >> n;
	int bn = n;
	while(((-n) & n) != n){
		n++;
	}
	
	solve(1,1,n,n);
	
	for(int i = 1;i <= bn;i++){
		for(int j = 1;j <= bn;j++){
			cout << a[i][j] << " ";
		}
		cout << "\n";
	}
	
	return 0;
}