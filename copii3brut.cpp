#define JUDGE 1

#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

FILE *f = fopen("copii3.in","r");
FILE *g = fopen("copii3.ok","w");

const int NMAX = 32e4;

int n,q;
char s[NMAX + 5];

long long prefix_sum[NMAX + 5];
int cnt_prefix_sum[NMAX + 5];

vector<int> pos0;

int last_0_in_prefix[NMAX + 5];
int first_0_in_suffix[NMAX + 5];

int taken_pos(int st,int dr){
	return cnt_prefix_sum[dr] - cnt_prefix_sum[st - 1];
}

int free_pos(int st,int dr){
	return (dr - st + 1) - (cnt_prefix_sum[dr] - cnt_prefix_sum[st - 1]);
}

long long sum_of_1_positions(int st,int dr){
	return prefix_sum[dr] - prefix_sum[st - 1];
}

long long sum_of_0_positions(int st,int dr){
	return 1LL * (dr - st + 1) * (st + dr) / 2 - (prefix_sum[dr] - prefix_sum[st - 1]);
}

long long check(int l,int r,int pos){///[l,pos][pos + 1,r]
	if(last_0_in_prefix[l - 1] - taken_pos(l,pos) + 1 < 0  || first_0_in_suffix[r + 1] + taken_pos(pos + 1,r) - 1 >= (int)pos0.size()){
		return 1LL << 62;
	}

	long long a = sum_of_1_positions(l,pos);
	long long b = last_0_in_prefix[l - 1] == -1 ? 0 : sum_of_0_positions(pos0[last_0_in_prefix[l - 1] - taken_pos(l,pos) + 1],pos0[last_0_in_prefix[l - 1]]);
	long long c = first_0_in_suffix[r + 1] == (int)pos0.size() ? 0 : sum_of_0_positions(pos0[first_0_in_suffix[r + 1]],pos0[first_0_in_suffix[r + 1] + taken_pos(pos + 1,r) - 1]);
	long long d = sum_of_1_positions(pos + 1,r);

	return a - b + c - d;
}

int first_good_pos(int l,int r){
    int st = l - 2,dr = r;
    while(dr - st > 1){
        int mid = (st + dr) / 2;
        if(first_0_in_suffix[r + 1] + taken_pos(mid + 1,r) - 1 >= (int)pos0.size()){
            st = mid;
        }
        else{
            dr = mid;
        }
    }

    return dr;
}

int last_good_pos(int l,int r){
    int st = l - 1,dr = r + 1;
    while(dr - st > 1){
        int mid = (st + dr) / 2;
        if(last_0_in_prefix[l - 1] - taken_pos(l,mid) + 1 < 0){
            dr = mid;
        }
        else{
            st = mid;
        }
    }
    return st;
}

int main(){

	fscanf(f,"%d %d\n",&n,&q);
	fgets(s + 1,NMAX + 2,f);

	last_0_in_prefix[0] = -1;

	for(int i = 1;i <= n;i++){
		prefix_sum[i] = (s[i] == '1' ? i : 0) + prefix_sum[i - 1];
		cnt_prefix_sum[i] = (s[i] == '1') + cnt_prefix_sum[i - 1];
		if(s[i] == '0'){
			pos0.push_back(i);
		}
		last_0_in_prefix[i] = (int)pos0.size() - 1;
	}

	int ind = (int)pos0.size();

	for(int i = n;i;i--){
		if(ind && pos0[ind - 1] == i){
			ind--;
		}
		first_0_in_suffix[i] = ind;
	}

	first_0_in_suffix[n + 1] = pos0.size();


	while(q--){
		int l,r;
		fscanf(f,"%d %d",&l,&r);

		long long ans = 1LL << 62;

		for(int i = l - 1;i <= r;i++){
			ans = min(ans,check(l,r,i));
		}

		fprintf(g,"%lld\n",ans == 1LL << 62 ? -1:ans);
	}

	return 0;
}
