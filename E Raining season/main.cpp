#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const int NMAX = 2e5;
const int MMAX = 1e6;

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

	long long operator () (long long x)const{
		return a * x + b;
	}

	bool operator < (const LinearFunction &other)const{
        if(a != other.a){
            return a < other.a;
        }
        return b < other.b;
	}
};

///max convex hull
class DynamicConvexHull{
private:
    vector<LinearFunction> fun;
public:

    DynamicConvexHull(){
        fun.clear();
    }

	void add(LinearFunction f){
        fun.push_back(f);
	}

	void build(){
        sort(fun.begin(),fun.end());
        int ind = 0;
        for(int i = 1; i < (int)fun.size();i++){
            while(ind >= 0 && fun[ind].a == fun[i].a && fun[ind].b <= fun[i].b){
                ind--;
            }

            while(ind >= 1 && (fun[ind].b - fun[i].b) * (fun[ind].a - fun[ind - 1].a) <= (fun[ind - 1].b - fun[ind].b) * (fun[i].a - fun[ind].a)){
                ind--;
            }

            fun[++ind] = fun[i];
        }
        fun.resize(ind + 1);
	}

	long long operator () (long long x){

	    if(fun.empty()){
            return 0;
	    }

        int st = 0,dr = (int)fun.size() - 1;
        while(dr - st > 1){
            int mid = (st + dr) / 2;
            if(fun[mid].b - fun[mid + 1].b <= x * (fun[mid + 1].a - fun[mid].a)){
                st = mid;
            }
            else{
                dr = mid;
            }
        }

        if(st + 1 < (int)fun.size() && fun[st].b - fun[st + 1].b <= x * (fun[st + 1].a - fun[st].a)){
           st++;
        }

        return fun[st](x);
	}

    void merge_with(const DynamicConvexHull &other,bool rebuild){
        for(auto it:other.fun){
            this->add(it);
        }
        if(rebuild){
            this->build();
        }
    }

    int sz(){
        return fun.size();
    }

    void compose(const DynamicConvexHull &other,bool rebuild){
        DynamicConvexHull ans;
        int i = 0;
        int j = 0;
        while(i < (int)fun.size() - 1 || j < (int)other.fun.size() - 1){
            ans.add(fun[i] + other.fun[j]);

            if(i == (int)fun.size() - 1){
                j++;
                continue;
            }

            if(j == (int)other.fun.size() - 1){
                i++;
                continue;
            }

            if((fun[i].b - fun[i + 1].b) * (other.fun[j + 1].a - other.fun[j].a) <= (other.fun[j].b - other.fun[j + 1].b) *  (fun[i + 1].a - fun[i].a)){
                i++;
            }
            else{
                j++;
            }
        }
        ans.add(fun[i] + other.fun[j]);
        if(rebuild){
            ans.build();
        }
        *this = ans;
    }

    void compose(LinearFunction &a){
        for(auto &it:fun){
            it = it + a;
        }
    }

    void write(int st,int dr){///[st,dr)
        int id = 0;
        for(int i = st;i < dr;i++){
            while(id != (int)fun.size() - 1 && fun[id].b - fun[id + 1].b <= i * (fun[id + 1].a - fun[id].a)){
                id++;
            }
            fprintf(stdout,"%I64d ",fun[id](i));
        }
    }
};

struct edge_t{
	int to;
	int id;
	LinearFunction cost;

	edge_t(){
		to = 0;
		cost = LinearFunction();
		id = 0;
	}

	edge_t(int to, LinearFunction cost,int id){
		this->to = to;
		this->cost = cost;
		this->id = id;
	}
};

int n,m;
int weight[2 * NMAX + 5];
vector<edge_t> graph[2 * NMAX + 5];
int last_edge_id;
LinearFunction edge_cost[2 * NMAX + 5];
DynamicConvexHull ans;

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
    queue< pair<int,int> > nodes;
    nodes.push({nod,tata});
    while(!nodes.empty()){
        int nod = nodes.front().first;
        int tata = nodes.front().second;
        nodes.pop();

        if((int)graph[nod].size() > 2 + (tata == 0)){
            graph[nod].swap(graph[++n]);
            if(tata){
                graph[nod].push_back(graph[n].back());///father
                graph[n].pop_back();
            }
            graph[nod].push_back(graph[n].back());///random vertex
            graph[n].pop_back();
            graph[nod].push_back(edge_t(n,LinearFunction(),++last_edge_id));
            graph[n].push_back(edge_t(nod,LinearFunction(),last_edge_id));
            edge_cost[last_edge_id] = LinearFunction();
            if(tata){
                swap(graph[nod][(int)graph[nod].size() - 3],graph[nod].back());
            }
            for(auto it:graph[n]){
                if(it.to != nod){
                    graph[it.to].back().to = n;
                }
            }
        }

        for(auto it:graph[nod]){
            if(it.to != tata){
                nodes.push({it.to,nod});
            }
        }

    }
}

bool viz[2 * NMAX + 5];

void centroid_weight_dfs(int nod){
    weight[nod] = 0;
	for(auto it:graph[nod]){
		if(!viz[it.id]){
			viz[it.id] = 1;
			centroid_weight_dfs(it.to);
			viz[it.id] = 0;
			weight[nod] += weight[it.to] + 1;
		}
	}
}

void get_hull(int nod,DynamicConvexHull &hull,LinearFunction &start){
    int num = 0;
	for(auto it:graph[nod]){
		if(!viz[it.id]){
            num++;
			viz[it.id] = 1;
			start.a += it.cost.a;
			start.b += it.cost.b;

			get_hull(it.to,hull,start);

			viz[it.id] = 0;
			start.a -= it.cost.a;
			start.b -= it.cost.b;
		}
	}

	if(!num){
        hull.add(start);
	}

}

void centroid_dfs(int nod){

	centroid_weight_dfs(nod);

	int sz = weight[nod];

	if(sz == 0){
        return ;
	}

	int centroid_u = nod,centroid_v = 0,id = 0;
	for(auto it:graph[nod]){
		if(!viz[it.id] && (!centroid_v || weight[centroid_v] < weight[it.to])){
			centroid_v = it.to;
			id = it.id;
		}
	}

	while(weight[centroid_v] > sz / 2){
        int best_continue = 0;
		for(auto it:graph[centroid_v]){
			if(!viz[it.id] && it.to != centroid_u && weight[it.to] >= weight[best_continue]){
				best_continue = it.to;
				id = it.id;
			}
		}
        centroid_u = centroid_v;
        centroid_v = best_continue;
	}

	viz[id] = 1;

	if(sz != 1){
		centroid_dfs(centroid_u);
		centroid_dfs(centroid_v);
	}

	DynamicConvexHull fst,snd;

	LinearFunction a(0,0),b(0,0);

	get_hull(centroid_u,fst,a);
	get_hull(centroid_v,snd,b);
	fst.build();
	snd.build();
    fst.compose(edge_cost[id]);
    fst.compose(snd,0);

    ans.merge_with(fst,0);

	viz[id] = 0;
}

const int LEN = 1e7;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    while('0' <= buff[ind] && buff[ind] <= '9'){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }
    return ans;
}

int main(){

	n = i32();
	m = i32();

	for(int i = 1;i < n;i++){
		int u,v,a,b;
		u = i32();v = i32();a = i32();b = i32();
		graph[u].push_back(edge_t(v,LinearFunction(a,b),++last_edge_id));
		graph[v].push_back(edge_t(u,LinearFunction(a,b),last_edge_id));
		edge_cost[last_edge_id] = LinearFunction(a,b);
	}

	predfs(1,0);

	remake_tree(1,0);

    assert(n != 1e5);


	centroid_dfs(1);

	ans.build();

	ans.write(0,m);
	return 0;
}
