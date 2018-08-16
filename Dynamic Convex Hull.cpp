#include <cstdio>
#include <algorithm>
#include <set>

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
		double x = ((double)other.b - this->b) / (this->a - other.a);
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
///in case of overflow change to double divisions in DedicatedLinearFunction comparator and isBad in DynamicConvexHull
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
			if(this->a != other.a){
                return this->a < other.a;
			}
			return this->b < other.b;
		}

		else if(this->isQuery()){
			if(other.isLast){
				return 1;
			}

			long long delta_b = other.nxt->b - other.b;
			long long delta_a = other.a - other.nxt->a;

			if(delta_a < 0){
                delta_a *= -1;
                delta_b *= -1;
			}

			return delta_b < this->b * delta_a;
		}

		else{
			if(this->isLast){
				return 0;
			}

			long long delta_b = this->nxt->b - this->b;
			long long delta_a = this->a - this->nxt->a;

			if(delta_a < 0){
                delta_a *= -1;
                delta_b *= -1;
			}

			return delta_b < other.b * delta_a;
		}
	}

};

///max convex hull
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

		return (ant->b - it->b) * (nxt->a - it->a) >= (it->b - nxt->b) * (it->a - ant->a);
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
			prev(it)->isLast = 0;
		}

		while(next(it) != end() && isBad(next(it))){
			erase(next(it));
		}

		it->nxt = next(it);
		it->isLast = (it->nxt == end());

	}
	long long operator () (long long x){
	    set<DedicatedLinearFunction> :: iterator f = (lower_bound(DedicatedLinearFunction(QUERY_NUM,x)));
		return (*f)(x);
	}
};
