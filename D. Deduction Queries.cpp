#include <cstdio>
#include <map>

using namespace std;

const int NMAX = 4e5;

int q;
int ans;

map<int,int> id;
int last_id;
pair<int,int> father[NMAX + 5];

int fi(int nod){
	if(!father[nod].first){
		return nod;
	}
	int aux = father[nod].first;
	int tmp = fi(father[nod].first);
	father[nod].second ^= father[aux].second;
	father[nod].first = tmp;
	return tmp;
}

void update(int x,int y,int val){

	if(!id.count(x)){
		id[x] = ++last_id;
		x = last_id;
	}

	else{
		x = id[x];
	}

	if(!id.count(y)){
		id[y] = ++last_id;
		y = last_id;
	}

	else{
		y = id[y];
	}

	int tmpx = x;
	int tmpy = y;

	x = fi(x);
	y = fi(y);

	if(x == y){
		return ;
	}

	father[x].first = y;
	father[x].second = father[tmpx].second ^ father[tmpy].second ^ val;
}

int query(int x,int y){

	if(!id.count(x)){
		id[x] = ++last_id;
		x = last_id;
	}

	else{
		x = id[x];
	}

	if(!id.count(y)){
		id[y] = ++last_id;
		y = last_id;
	}

	else{
		y = id[y];
	}

	if(fi(x) != fi(y)){
		return -1;
	}

	return father[x].second ^ father[y].second;
}

int main(){

	scanf("%d",&q);

	int last = 0;

	while(q--){
		int t,x,y,val;
		scanf("%d %d %d",&t,&x,&y);

		x ^= last;
		y ^= last;


		if(x > y){
			swap(x,y);
		}
		y++;

		if(t == 1){
			scanf("%d",&val);
			val ^= last;
			update(x,y,val);
		}
		else{
			printf("%d\n",last = query(x,y));
			if(last == -1){
				last = 1;
			}
		}
	}

	return 0;
}