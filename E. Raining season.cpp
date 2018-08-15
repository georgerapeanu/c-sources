#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

const long long QUERY_NUM = 1LL << 62;

class LinearFunction{
public:
	long long a;
	long long b;

	LinearFunction(){
		a = b = 0;
	}
	
	LinearFunction(long long a, long long b){
		this->a = a;
		this->b = b;
	}
	
	LinearFunction operator + (const LinearFunction &other)const{
		return LinearFunction(a + other.a,b + other.b);	
	}
	
	LinearFunction operator - (const LinearFunction &other)const{
		return LinearFunction(a - other.a,b - other.b);	
	}
	
	pair<double,double> sect(const LinearFunction &other)const{
		double x = (other.b - this->b) / (this->a - other.a);
		double y = a * x + b;
		return make_pair(x,y);
	}
	
	bool paralel(const LinearFunction &other)const{
		return this->a == other.a;
	}
	
	long long operator () (int x)const{
		return a * x + b;
	}
};


///ads comparator between functions and the posibility of queries
///a query has a = QUERY_NUM and b is the query's searched x
class DedicatedLinearFunction:public LinearFunction{

public:
	
	mutable set<DedicatedLinearFunction>::iterator nxt;	
	mutable bool isLast;

	DedicatedLinearFunction(){
		a = b = 0;
	}
	
	DedicatedLinearFunction(long long a,long long b){
		this->a = a;
		this->b = b;
	}

	bool isQuery()const{
		return this->a == QUERY_NUM;
	}

	bool operator < (const DedicatedLinearFunction &other)const{
		if(!this->isQuery() && !other.isQuery()){
			return this->a < other.a;
		}
		
		else if(this->isQuery()){
			if(other.isLast){
				return 1;
			}
			return other.nxt->b - other.b < this->b * (other.a - other.nxt->a);
		}
		
		else{
			if(this->isLast){
				return 0;
			}
			return this->nxt->b - this->b < other.b * (this->a - this->nxt->a);
		}
	}
	
};

class DynamicConvexHull:public set<DedicatedLinearFunction>{
private:
	
	bool isBad(set<DedicatedLinearFunction>::iterator it){
		if((int)size() == 1){
			return 0;
		}
		
		if(it == begin()){
			set<DedicatedLinearFunction>::iterator nxt = next(it);
			return it->b <= nxt->b;
		}
		
		if(next(it) == end()){
			set<DedicatedLinearFunction>::iterator ant = prev(it);
			return ant->a == it->a && ant->b >= it->b;
		}
		
		set<DedicatedLinearFunction>::iterator nxt = next(it);
		set<DedicatedLinearFunction>::iterator ant = prev(it);
		
		if(it->paralel(*ant) && ant->b >= it->b){
			return 1;
		}
		
		if(it->paralel(*nxt) && nxt->b >= it->b){
			return 1;
		}
		
		return (it->b - ant->b) * (nxt->a - it->a) >= (it->b - nxt->b) * (ant->a - it->a);
	}
	
public:
	
	void add(DedicatedLinearFunction f){
		set<DedicatedLinearFunction>::iterator it = insert(f).first;
		if(isBad(it)){
			erase(it);
			return ;
		}
		
		while(it != begin() && isBad(prev(it))){
			erase(prev(it));
		}
		
		if(it != begin()){
			prev(it)->nxt = it;
		}
		
		while(next(it) != end() && isBad(next(it))){
			erase(next(it));
		}
		
		it->nxt = next(it);
		it->isLast = (it->nxt == end());
		
	}
	long long query(long long x){
		return (*lower_bound(DedicatedLinearFunction(x,QUERY_NUM)))(x);
	}
};
///test this and save it as a different file because it can be of use later
int main(){
	return 0;
}