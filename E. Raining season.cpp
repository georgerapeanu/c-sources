#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const long long QUERY_NUM = 1LL << 62;
const int NMAX = 200000;
const int MMAX = 1000000;

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

struct edge_t{
	int to;
	int id;
	DedicatedLinearFunction cost;
	
	edge_t(){
		to = 0;
		cost = DedicatedLinearFunction();
		id = 0;
	}
	
	edge_t(int to, DedicatedLinearFunction cost,int id){
		this->to = to;
		this->cost = cost;
		this->id = id;
	}
};

int n,m;
int weight[NMAX + 5];
vector<edge_t> graph[NMAX + 5];
int last_edge_id;

long long ans[MMAX + 5];

void predfs(int nod,int tata){

	for(auto &it:graph[nod]){
		if(it.to == tata){
			swap(it,graph[nod].back());
			break;
		}
	}
	
	for(auto it:graph[nod]){
		if(it.to != tata){
			predfs(it.to,nod);
		}
	}

}

void remake_tree(int nod,int tata){
	if((int)graph[nod].size() > 3){
		swap(graph[nod],graph[++n]);
		graph[nod].push_back(graph[n].back());///father
		graph[n].pop_back();
		graph[nod].push_back(graph[n].back());///random vertex
		graph[n].pop_back();
		graph[nod].push_back(edge_t(n,DedicatedLinearFunction(),++last_edge_id));
		graph[n].push_back(edge_t(nod,DedicatedLinearFunction(),last_edge_id));
	}
	
	for(auto it:graph[nod]){
		if(it.to != tata){
			remake_tree(it.to,nod);
		}
	}		
}

bool viz[100005];

void centroid_weight_dfs(int nod){
	weight[nod] = 1;
	for(auto it:graph[nod]){
		if(!viz[it.id]){
			viz[it.id] = 1;
			centroid_predfs(it.to,nod);
			viz[it.id] = 0;
			weight[nod] += weight[it.to];
		}
	}
}

void get_hull(int nod,DynamicConvexHull &hull,DedicatedLinearFunction &start){
	
}

void centroid_dfs(int nod){
	
	centroid_weight_dfs(nod);
	
	int sz = weight[nod];
	int centroid_u = nod,centroid_v = 0,id = 0;
	for(auto it:graph[nod]){
		if(!viz[it.id] && (!centroid_v || weight[centroid_v] < weight[it.to]){
			centroid_v = it.to;
			id = it.id;
		}
	}
	
	while(weight[centroid_w] > sz / 2){
		for(auto it:graph[centroid_v]){
			if(!viz[it.id] && it.to != centroid_u && weight[it.to] > sz / 2){
				centroid_u = centroid_v;
				centroid_v = it.to;
				id = it.id;
				break;
			}				
		}
	}
	
	viz[id] = 1;
	
	if(sz != 2){
		centroid_dfs(centroid_u);
		centroid_dfs(centroid_v);
	}
	
	DynamicConvexHull fst,snd;
	
	get_hull(centroid_u,fst,DedicatedLinearFunction());
	get_hull(centroid_v,snd,DedicatedLinearFunction());
	
	for(int t = 0;t < m;t++){
		ans[t] = max(ans[t],fst(t) + snd(t));
	}
	
	viz[id] = 0;
}

int main(){
	
	
	
	return 0;
}