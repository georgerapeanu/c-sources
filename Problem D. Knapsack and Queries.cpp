#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdint> //uint8_t, uint32_t

using namespace std;
 
class Crypto {
public:    
    Crypto() {
        sm = cnt = 0;
        seed();
    }
    
    int decode(int z) {
        z ^= next();
        z ^= (next() << 8);
        z ^= (next() << 16);
        z ^= (next() << 22);
        return z;
    }
 
    void query(long long z) {
        const long long B = 425481007;
        const long long MD = 1000000007;
        cnt++;
        sm = ((sm * B % MD + z) % MD + MD) % MD;
        seed();
    }
private: 
    long long sm;
    int cnt;
 
    uint8_t data[256];
    int I, J;
 
    void swap_data(int i, int j) {
        uint8_t tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;    
    }
 
    void seed() {
        uint8_t key[8];
        for (int i = 0; i < 4; i++) {
            key[i] = (sm >> (i * 8));
        }
        for (int i = 0; i < 4; i++) {
            key[i+4] = (cnt >> (i * 8));
        }
 
        for (int i = 0; i < 256; i++) {
            data[i] = i;
        }
        I = J = 0;
 
        int j = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + data[i] + key[i%8]) % 256;
            swap_data(i, j);
        }
    }
 
    uint8_t next() {
        I = (I+1) % 256;
        J = (J + data[I]) % 256;
        swap_data(I, J);
        return data[(data[I] + data[J]) % 256];
    }
};
	
int MOD, Q;
struct stack_node_t{
	int w;
	int v;
	vector<long long> dp;
	
	stack_node_t(int w,int v){
		this->w = w;
		this->v = v;
		vector<long long> base(MOD,-(1LL << 60));
		base[0] = 0;
		dp = base;
		for(int i = 0;i < (int)base.size();i++){
			dp[(i + w) % MOD] = max(dp[(i + w) % MOD],max(-(1LL << 60),base[i] + v));
		}
	}
	
	stack_node_t(int w,int v,vector<long long> &base){
		this->w = w;
		this->v = v;
		dp = base;
		for(int i = 0;i < (int)base.size();i++){
			dp[(i + w) % MOD] = max(dp[(i + w) % MOD],max(-(1LL << 60),base[i] + v));
		}
	}
};

vector< stack_node_t > fst_stack;
vector< stack_node_t > snd_stack;

void add(int w,int v){
	if(snd_stack.empty()){
		snd_stack.push_back(stack_node_t(w,v));
	}
	else{
		snd_stack.push_back(stack_node_t(w,v,snd_stack.back().dp));
	}
}

void rem(){
	if(fst_stack.empty()){
		fst_stack.push_back(stack_node_t(snd_stack.back().w,snd_stack.back().v));
		snd_stack.pop_back();
		
		while(!snd_stack.empty()){
			fst_stack.push_back(stack_node_t(snd_stack.back().w,snd_stack.back().v,fst_stack.back().dp));
			snd_stack.pop_back();
		}
	}
	fst_stack.pop_back();
}

long long fi(int l,int r){
	vector<long long> fst;
	vector<long long> snd;
	
	if(fst_stack.empty()){
		fst = vector<long long>(MOD,-(1LL << 60));
		fst[0] = 0;
	}
	else{
		fst = fst_stack.back().dp;
	}
	
	if(snd_stack.empty()){
		snd = vector<long long>(MOD,-(1LL << 60));
		snd[0] = 0;
	}
	else{
		snd = snd_stack.back().dp;
	}
	
	deque<pair<long long,int> > max_dq;
	
	for(int i = r;i >= l;i--){
		while(!max_dq.empty() && max_dq.back().first <= snd[i]){
			max_dq.pop_back();
		}
		max_dq.push_back({snd[i],i});
	}
	
	long long ans = -(1LL << 60);
	
	for(int i = 0;i < MOD;i++){
		ans = max(ans,fst[i] + max_dq.front().first);
		
		if(max_dq.front().second == r){
			max_dq.pop_front();
		}
		
		r = (r == 0 ? MOD - 1:r - 1);
		l = (l == 0 ? MOD - 1:l - 1);
		
		while(!max_dq.empty() && max_dq.back().first <= snd[l]){
			max_dq.pop_back();
		}
		
		max_dq.push_back({snd[l],l});
	}
	
	return (ans < 0 ? -1:ans);
}

int main() {
	
	freopen("in","r",stdin);
	freopen("out","w",stdout);

	scanf("%d %d", &MOD, &Q);

	Crypto c;

	for (int i = 0; i < Q; i++) {
		int t, w, v, l, r;
		scanf("%d %d %d %d %d", &t, &w, &v, &l, &r);
		t = c.decode(t);
		w = c.decode(w);
		v = c.decode(v);
		l = c.decode(l);
		r = c.decode(r);

		if (t == 1) {
			add(w,v);
		} 
		
		else {
			rem();
		}
		
		
		long long ans = fi(l,r);
		c.query(ans);
		printf("%lld\n", ans);
	}
	
	return 0;
}
