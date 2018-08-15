#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int N,Q,X;

struct node{
	long long sum;
	int val,max_val;
	int lazy;
};

node AINT[400005];///ans[N + 1] = inf;
int V[100005];
int S[21][100005];

void propag(int nod,int st,int dr){
	if(st == dr || !AINT[nod].lazy){
		return;
	}

	if(AINT[nod].lazy == -1){
		AINT[2 * nod].val = AINT[2 * nod + 1].val = N + 1;
		AINT[2 * nod].max_val = AINT[2 * nod + 1].max_val = N + 1;
		AINT[2 * nod].lazy = AINT[2 * nod + 1].lazy = -1;
		int mid = (st + dr) / 2;
		AINT[2 * nod].sum = 1LL * (N + 1) * (mid - st + 1);
		AINT[2 * nod + 1].sum = 1LL * (N + 1) * (dr - mid);
	}

	else{
		AINT[2 * nod].val = min(AINT[2 * nod].val,AINT[nod].lazy);
		AINT[2 * nod].max_val = min(AINT[2 * nod].val,AINT[nod].lazy);///
		AINT[2 * nod + 1].val = min(AINT[2 * nod + 1].val,AINT[nod].lazy);
		AINT[2 * nod + 1].max_val = min(AINT[2 * nod + 1].val,AINT[nod].lazy);///
		AINT[2 * nod].lazy = min((AINT[2 * nod].lazy <= 0 ? (1 << 20) : AINT[2 * nod].lazy),AINT[nod].lazy);
		AINT[2 * nod + 1].lazy = min((AINT[2 * nod + 1].lazy <= 0 ? (1 << 20) : AINT[2 * nod + 1].lazy),AINT[nod].lazy);
		int mid = (st + dr) / 2;
		AINT[2 * nod].sum = 1LL * (AINT[2 * nod].val) * (mid - st + 1);///
		AINT[2 * nod + 1].sum = 1LL * (AINT[2 * nod + 1].val) * (dr - mid);///
	}

	AINT[nod].lazy = 0;
}

void u(int nod,int st,int dr,int S,int D,int val){
	propag(nod,st,dr);

	if(S <= st && dr <= D){
		if(val == -1){
			AINT[nod].val = N + 1;
			AINT[nod].max_val = N + 1;
			AINT[nod].lazy = -1;
			AINT[nod].sum = 1LL * AINT[nod].val * (dr - st + 1);
		}
		else{
			AINT[nod].val = AINT[nod].max_val = min(AINT[nod].val,val);
			AINT[nod].lazy = min((AINT[nod].lazy <= 0 ? (1 << 20) : AINT[nod].lazy),val);
			AINT[nod].sum = 1LL * AINT[nod].val * (dr - st + 1);
		}
		return ;
	}

	if(S > dr || D < st){
		return ;
	}

	int mid = (st + dr) / 2;

	u(nod * 2,st,mid,S,D,val);
	u(nod * 2 + 1,mid + 1,dr,S,D,val);

	AINT[nod].val = min(AINT[nod * 2].val,AINT[2 * nod + 1].val);
	AINT[nod].max_val = max(AINT[nod * 2].max_val,AINT[2 * nod + 1].max_val);
	AINT[nod].sum = AINT[2 * nod].sum + AINT[2 * nod + 1].sum;
}

long long q(int nod,int st,int dr,int S,int D){
	propag(nod,st,dr);

	if(st > D || dr < S){
		return 0;
	}

	if(st == dr){
		return AINT[nod].sum;
	}

	int mid = (st + dr) / 2;

	return q(nod * 2,st,mid,S,D) + q(nod * 2 + 1,mid + 1,dr,S,D);
}

int OR_AINT[400005];

void OR_u(int nod,int st,int dr,int pos,int val){
	if(dr < pos || st > pos){
		return ;
	}

	if(st == dr){
		OR_AINT[nod] = val;
		return ;
	}

	int mid = (st + dr) / 2;

	OR_u(nod * 2,st,mid,pos,val);
	OR_u(nod * 2 + 1,mid + 1,dr,pos,val);

	OR_AINT[nod] = OR_AINT[2 * nod] | OR_AINT[2 * nod + 1];

}

int OR_q(int nod,int st,int dr,int S,int D){
	if(S <= st && dr <= D){
		return OR_AINT[nod];
	}

	if(S > dr || D < st){
		return 0;
	}

	int mid = (st + dr) / 2;

	return OR_q(nod * 2,st,mid,S,D) | OR_q(nod * 2 + 1,mid + 1,dr,S,D);
}

void afis(int nod,int st,int dr){
	propag(nod,st,dr);
	cout << nod << " " << st << " " << dr << " ";
	cout << AINT[nod].sum << " " << AINT[nod].val << " " << AINT[nod].lazy << "\n";

	if(st == dr){
		return ;
	}

	int mid = (st + dr) / 2;

	afis(nod * 2,st,mid);
	afis(nod * 2 + 1,mid + 1,dr);
}

int first_greater(int nod,int st,int dr,int val){
	propag(nod,st,dr);
	if(st == dr){
		return st;
	}

	int mid = (st + dr) / 2;

	if(AINT[2 * nod].max_val >= val){
		return first_greater(2 * nod,st,mid,val);
	}
	else{
		return first_greater(2 * nod + 1,mid + 1,dr,val);
	}
}

int last_smaller(int nod,int st,int dr,int val){
	propag(nod,st,dr);
	if(st == dr){
		return st;
	}

	int mid = (st + dr) / 2;

	if(AINT[2 * nod + 1].val <= val){
		return last_smaller(2 * nod + 1,mid + 1,dr,val);
	}
	else{
		return last_smaller(2 * nod,st,mid,val);
	}
}

int find_leaf(int nod,int st,int dr,int pos){

	if(st > pos || dr < pos){
		return 0;
	}

	if(st == dr){
		return nod;
	}

	int mid = (st + dr) / 2;

	return max(find_leaf(nod * 2,st,mid,pos),find_leaf(nod * 2 + 1,mid + 1,dr,pos));

}

pair<int,int> get_range(int target){
	vector<int> tmp;
	while(target){
		tmp.push_back(target);
		target /= 2;
	}

	int st = 1,dr = N + 1;
	for(int i = (int)tmp.size() - 2;i >= 0;i--){
		if(tmp[i] % 2 == 0){
			dr = (st + dr) / 2;
		}
		else{
			st = (st + dr) / 2 + 1;
		}
	}

	return {st,dr};
}

int find_last_OR(int right){
	if(V[right] >= X){
		return right;
	}
	int nod = find_leaf(1,1,N + 1,right),OR = V[right];
	while(1){
		if(nod % 2 == 0){
			nod /= 2;
			continue;
		}

		if(nod == 1){
			break;
		}

		if((OR_AINT[nod - 1] | OR) < X){
			OR |= OR_AINT[nod - 1];
			nod /= 2;
		}

		else{
			break;
		}
	}

	if(nod == 1){
		return 0;
	}

	nod--;

	pair<int,int> tmp = get_range(nod);

	int st = tmp.first;
	int dr = tmp.second;

	while(st != dr){
		int mid = (st + dr) / 2;
		if((OR | (OR_AINT[2 * nod + 1])) < X){
			OR |= (OR_AINT[2 * nod + 1]);
			nod *= 2;
			dr = mid;
		}
		else{
			nod = nod * 2 + 1;
			st = mid + 1;
		}
	}

	return st;
}

void build(int nod,int st,int dr){
    if(st == dr){
        AINT[nod] = {N + 1,N + 1,N + 1,N + 1};
        return;
    }
    int mid = (st + dr) / 2;
    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
    AINT[nod].val = AINT[nod].max_val = N + 1;
    AINT[nod].sum = 1LL * (dr - st + 1) * (N + 1);
}

void up(int id,int pos,int val){
	for(;pos <= N + 1;pos += (-pos) & pos){
		S[id][pos] += val;
	}
}

int AIB_q(int id,int left){
	int sum_at_left = 0,pos = 0;
	for(int i = (1 << 17);i;i >>= 1){
		if(left & i){
			pos += i;
			sum_at_left += S[id][pos];
		}
	}
	
	pos = 0;
	
	int sum = 0;
	
	for(int i = (1 << 17);i;i >>= 1){
		if(pos + i <= N + 1 && sum + S[id][pos + i] <= sum_at_left){
			pos += i;
			sum += S[id][pos];
		}
	}
	return pos + 1;
}

int main(){
	scanf("%d %d %d",&N,&Q,&X);

	u(1,1,N + 1,1,N + 1,-1);
    build(1,1,N + 1);
	for(int i = 1;i <= N;i++){
		scanf("%d",&V[i]);
		OR_u(1,1,N + 1,i,V[i]);
		for(int b = 0;b < 20;b++){
			if((V[i] >> b) & 1){
				up(b,i,1);
			}
		}
	}

	V[N + 1] = (1 << 20) - 1;

	OR_u(1,1,N + 1,N + 1,(1 << 20) - 1);

	for(int b = 0;b < 20;b++){
		up(b,N + 1,1);
	}

	int last = 0;

	for(int i = 1;i <= N;i++){
		int st = find_last_OR(i);

		if(st > last){
			u(1,1,N + 1,last + 1,st,i);
			last = st;
		}
	}

	///afis(1,1,N + 1);

	while(Q--){
		int t,l,r;
		scanf("%d %d %d",&t,&l,&r);
		if(t == 1){

			vector<int> pos;
			pos.push_back(l);
			for(int b = 0;b < 20;b++){
				pos.push_back(AIB_q(b,l));
			}

			sort(pos.begin(),pos.end());
			pos.resize(unique(pos.begin(),pos.end()) - pos.begin());

			for(int b = 0;b < 20;b++){
				if((V[l] >> b) & 1){
					up(b,l,-1);
				}
				if((r >> b) & 1){
					up(b,l,1);
				}
			}

			V[l] = r;

			OR_u(1,1,N + 1,l,r);

			int dr = first_greater(1,1,N + 1,l);

			u(1,1,N + 1,dr,l,-1);

			int last = 0;

			for(int i = 0;i < (int)pos.size();i++){
				int st = find_last_OR(pos[i]);
				if(min(st,l) > last){
					u(1,1,N + 1,last + 1,min(st,l),pos[i]);
					last = min(st,l);
				}
			}

		}
		else{
			int st = last_smaller(1,1,N + 1,r);

			printf("%I64d\n",1LL * (max(0,st - l + 1)) * (r + 1) - (l <= st ? q(1,1,N + 1,l,st) : 0));
		}
	}

	return 0;
}
