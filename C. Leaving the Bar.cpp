#include <iostream>
#include <algorithm>

using namespace std;

int nxt_ind,cN;

struct geom_vector{
	int a,b;
	int ind;
	int left,right;///composition things
	int sgn;

	geom_vector(){

	}

	geom_vector(int c,int d,int i,int l,int r,int s){
		a = c;
		b = d;
		ind = i;
		left = l;
		right = r;
		sgn = s;
	}

	geom_vector operator + (const geom_vector &other)const{
		return geom_vector(a + other.a,b + other.b,0,ind,other.ind,1);
	}

	geom_vector operator - (const geom_vector &other)const{
		return geom_vector(a - other.a,b - other.b,0,ind,other.ind,-1);
	}

	double magnitude(){
		return sqrt(1.0 * a * a + 1.0 * b * b);
	}
}V[200005],VV[200005];

int N;
int sgn[200005];

void dfs(int nod,int Sign){
	if(nod <= cN){
		sgn[nod] = Sign;
		return ;
	}
	dfs(VV[nod].left,Sign);
	dfs(VV[nod].right,Sign * VV[nod].sgn);
}

int main(){

	cin >> N;nxt_ind = N + 1;

	cN = N;

	for(int i = 1;i <= N;i++){
		cin >> V[i].a >> V[i].b;
		V[i].ind = i;
		V[i].left = 0;
		V[i].right = 0;
		V[i].sgn = 1;
		VV[i] = V[i];
	}

	while(N > 2){
		for(int i = N - 2;i <= N;i++){
			for(int j = N - 2;j <= N;j++){
				if(i != j && (V[i] + V[j]).magnitude() <= 1e6){
					geom_vector v1 = V[i] + V[j];
					geom_vector v2 = V[(N - 2) ^ (N - 1) ^ N ^ i ^ j];
					N--;
					v1.ind = nxt_ind++;
					VV[v1.ind] = v1;
					V[N - 1] = v1;
					V[N] = v2;
					goto done;
				}
				else if(i != j && (V[i] - V[j]).magnitude() <= 1e6){
					geom_vector v1 = V[i] - V[j];
					geom_vector v2 = V[(N - 2) ^ (N - 1) ^ N ^ i ^ j];
					N--;
					v1.ind = nxt_ind++;
					VV[v1.ind] = v1;
					V[N - 1] = v1;
					V[N] = v2;
					goto done;
				}
			}
		}
		done:;
	}

	if((V[1] + V[2]).magnitude() <= 1e6){
		V[1] = V[1] + V[2];
		V[1].ind = nxt_ind++;
		VV[V[1].ind] = V[1];
	}
	else{
		V[1] = V[1] - V[2];
		V[1].ind = nxt_ind++;
		VV[V[1].ind] = V[1];
	}

	dfs(V[1].ind,1);

	for(int i = 1;i <= cN;i++){
		cout << sgn[i] << " ";
	}

	cout << "\n";

	return 0;
}
