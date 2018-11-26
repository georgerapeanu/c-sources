#include <cstdio>
 
using namespace std;
 
FILE *f = fopen("squirrel.in","r");
FILE *g = fopen("squirrel.out","w");
 
int n,m,q;
const int dx[] = {-1,-1,0,1,1,1,0,-1};
const int dy[] = {0,1,1,1,0,-1,-1,-1};
 
int ans;
 
long long mask[50005];
int fst_prime[50005];
int nr = 0;
 
inline bool chk(int a,int b){
	if(a == 0 || b == 0){
		return (a + b == 1);
	}
	
	if(fst_prime[a] != 0 && fst_prime[a] == fst_prime[b]){
		return false;
	}
	
	return (mask[a] & mask[b]) == 0;
}
 
void draw(int x,int y,int sz,int dir){
	for(int i = 1;i <= sz;i++){
		x += dx[dir];
		y += dy[dir];
		ans += chk(x,y);
	}
	
	if(sz == 1){
		return ;
	}
	
	sz /= 2;
	
	int nd = ((dir + 1) & 7);
	
	for(int i = 1;i <= sz;i++){
		ans += chk(x + dx[nd] * i,y + dy[nd] * i);
	}
	
	draw(x + dx[nd] * sz,y + dy[nd] * sz,sz,((nd + 1) & 7));
	draw(x + dx[nd] * sz,y + dy[nd] * sz,sz,((nd + 7) & 7));
	
	nd = ((dir + 7) & 7);
	
	for(int i = 1;i <= sz;i++){
		ans += chk(x + dx[nd] * i,y + dy[nd] * i);
	}
	
	draw(x + dx[nd] * sz,y + dy[nd] * sz,sz,((nd + 1) & 7));
	draw(x + dx[nd] * sz,y + dy[nd] * sz,sz,((nd + 7) & 7));
}
 
int main(){
	
	for(int i = 2;i <= 50000;i++){
		if(mask[i] || fst_prime[i]){
			continue;
		}
		if(nr <= 60){
			mask[i] |= 1LL << nr;
			nr++;
			for(int j = 2 * i;j <= 50000;j += i){
				mask[j] |= mask[i];
			}
		}
		else{///they will be bigger than sqrt
			for(int j = i;j <= 50000;j += i){
				fst_prime[j] = i;
			}
		}
	}
	
	fscanf(f,"%d %d %d",&n,&m,&q);
	
	while(q--){
		int x,y,gr;
		fscanf(f,"%d %d %d",&x,&y,&gr);
		x--;
		y--;
		draw(x,y,gr,0);
		ans += (chk(x,y));
	}
	
	fprintf(g,"%d",ans);
			
	fclose(f);
	fclose(g);
	
	return 0;
}
