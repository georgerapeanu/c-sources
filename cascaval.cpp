#include <cstdio>
#include <iostream>
#include <set>

using namespace std;

FILE *f = fopen("cascaval.in","r");
FILE *g = fopen("cascaval.out","w");

const long long IS_QUERRY = -1;

struct linear_function_t{
	long long a,b;
	mutable set<linear_function_t> :: iterator nxt;
	mutable bool is_last;
	
	linear_function_t(){
		a = b = 0;
		is_last = true;
	}
	
	linear_function_t(long long a,long long b){
		this->a = a;
		this->b = b;
	}
	
	bool operator < (const linear_function_t &other)const{
		if(other.b != IS_QUERRY && this->b != IS_QUERRY){
			if(a != other.a){
				return a > other.a;
			}
			return b > other.b;
		}
		
		if(other.b == IS_QUERRY){
			
			if(this->is_last){
				return false;
			}
			
			if(double(nxt->b - this->b) / (this->a - nxt->a) <= other.a){
				return true;
			}
			return false;
		}
		
		return !(other < *this);
	}
	
	long long operator () (long long x)const{
		return a * x + b;
	}
};

class DynamicConvexHull{

private:

	set<linear_function_t> fun;
	long long offset;
	
	
	bool bad(set<linear_function_t> :: iterator it){
		
		if(fun.size() == 1){
			return false;
		}
		
		if(it == fun.begin()){
			if(it->a == next(it)->a && it->b >= next(it)->b){
				return true;
			}
			return false;
		}
		
		if(next(it) == fun.end()){
			if(it->a == prev(it)->a && it->b >= prev(it)->b){
				return true;
			}
			return false;
		}
		
		if(double(next(it)->b - prev(it)->b) / (prev(it)->a - next(it)->a) < double(it->b - prev(it)->b) / (prev(it)->a - it->a)){
			return true;
		}
		return false;
	}
	
public:
	
	DynamicConvexHull(){
		offset = 0;
		fun.clear();
	}
	
	void ins(linear_function_t a){
		a.a -= offset;
		auto tmp = fun.insert(a);
		
		if(tmp.second == false){
			return;
		}
		
		set<linear_function_t>::iterator it = tmp.first;
		
		if(bad(it)){
			fun.erase(it);
			return;
		}
		
		while(it != fun.begin() && bad(prev(it))){
			fun.erase(prev(it));
		}
		
		if(it != fun.begin()){
			prev(it)->nxt = it;
			prev(it)->is_last = false;
		}
		
		while(next(it) != fun.end() && bad(next(it))){
			fun.erase(next(it));
		}
		
		if(next(it) != fun.end()){
			it->nxt = next(it);
			it->is_last = false;
		}
		else{
			it->is_last = true;
		}
	}
	
	query(long long x){
		return (*fun.lower_bound({x,IS_QUERRY}))(x) + offset * x;
	}
	
	void add_offset(long long val){
		offset += val;
	}		

};

const int NMAX = 1e5;

int n;
long long dp[NMAX + 5][2];

int main(){
	
	fscanf(f,"%d",&n);
	
	DynamicConvexHull hull;
	
	for(int i = 1;i <= n;i++){
		int b,a,s,d;
		fscanf(f,"%d %d %d %d",&b,&a,&s,&d);
		if(i == 1){
			dp[i][0] = 1LL << 60;
			dp[i][1] = b + 1LL * a * d;
		}
		else{
			dp[i][0] = hull.query(d);
			dp[i][1] = min(min(dp[i - 1][0],dp[i - 1][1]) + b + 1LL * a * d,dp[i][0] + b);
		}
		
		hull.ins(linear_function_t(d,dp[i][1]));
		hull.add_offset(s);
	}
	
	fprintf(g,"%lld",min(dp[n][1],dp[n][0]));
	
	fclose(f);
	fclose(g);
	
	return 0;
}