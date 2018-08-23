#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

struct event_t{
	int len;
	int id;
	bool is_query;

	event_t(){
		len = 0;
		id = 0;
		is_query = 0;
	}

	event_t(int len,int id,bool is_query){
		this->len = len;
		this->id = id;
		this->is_query = is_query;
	}

	bool operator < (const event_t &other)const{
		if(len != other.len){
			return len < other.len;
		}
		if(id != other.id){
			return id < other.id;
		}
		return is_query < other.is_query;
	}
};

class DSU{
public:
	int father[NMAX + 5];
	int sz[NMAX + 5];
	int weight[NMAX + 5];
	int last_element[NMAX + 5];

	DSU(){
		memset(father,0,sizeof(father));
		memset(sz,0,sizeof(sz));
		memset(weight,0,sizeof(weight));
		memset(last_element,0,sizeof(last_element));

		for(int i = 1;i <= NMAX;i++){
			sz[i] = 1;
			last_element[i] = i;
			weight[i] = 1;
		}
	}

	int get_root(int a){
		if(father[a] == 0){
			return a;
		}
		return father[a] = get_root(father[a]);
	}

	void join(int a,int b){
		a = get_root(a);
		b = get_root(b);
		if(sz[a] < sz[b]){
			sz[b] += sz[a];
			father[a] = b;
			weight[b] = min(weight[a],weight[b]);
			last_element[b] = max(last_element[a],last_element[b]);
		}
		else{
			sz[a] += sz[b];
			father[b] = a;
			weight[a] = min(weight[a],weight[b]);
			last_element[a] = max(last_element[a],last_element[b]);
		}
	}

	int get_size(int a){
		return sz[get_root(a)];
	}

	int get_weight(int a){
		return weight[get_root(a)] && get_size(a) % 2 == 1;
	}

	int get_last_element(int a){
		return last_element[get_root(a)];
	}
};

int n,q;
int points[NMAX + 5];
int lengths[NMAX + 5];
DSU active_lengths;
set<event_t> what_is_happening;
long long ans[NMAX + 5];
int last_timeout[NMAX + 5];
bool timedout[NMAX + 5];
int remaining_queries;

int main() {

	fscanf(stdin,"%d %d",&n,&q);

	for(int i = 1;i <= n;i++){
		fscanf(stdin,"%d",&points[i]);
	}

	int sz = 1;

	for(int i = 2;i <= n;i++){
		if(points[sz - 1] <= points[sz] && points[sz] <= points[i]){
			points[sz] = points[i];
		}

		else if(points[sz - 1] >= points[sz] && points[sz] >= points[i]){
			points[sz] = points[i];
		}

		else{
			points[++sz] = points[i];
		}
	}

	long long initial_cost = 0;
	int initial_len = 0;
    int delta = sz;

	for(int i = 1;i <= sz;i++){
		lengths[i] = abs(points[i] - points[i - 1]);
		initial_cost += lengths[i];
	}

	if(points[1] < 0){
		for(int i = 1;i <= sz;i++){
			lengths[i] = lengths[i + 1];
		}
		sz--;
		delta--;
	}

	for(int i = 1;i <= sz;i++){
		what_is_happening.insert(event_t(lengths[i],i,0));
	}

	for(int i = 1;i <= q;i++){
		int len;
		fscanf(stdin,"%d",&len);
		what_is_happening.insert(event_t(len,i,1));
	}

	remaining_queries = q;

	while(remaining_queries){
		event_t event = *what_is_happening.begin();
		what_is_happening.erase(what_is_happening.begin());

		initial_cost -= 1LL * delta * (event.len - initial_len);
		initial_len = event.len;

		if(event.is_query){
			ans[event.id] = initial_cost;
			remaining_queries--;
		}
		else{
			delta -= active_lengths.get_weight(event.id);

			if(event.id < sz){
				delta -= active_lengths.get_weight(event.id + 1);
				active_lengths.join(event.id,event.id + 1);
				delta += active_lengths.get_weight(event.id);
				if(active_lengths.get_size(event.id) % 2 == 0){
					if(!timedout[active_lengths.get_last_element(event.id)]){
						last_timeout[active_lengths.get_last_element(event.id)] = event.len;
						timedout[active_lengths.get_last_element(event.id)] = 1;
						what_is_happening.erase(event_t(lengths[active_lengths.get_last_element(event.id)],active_lengths.get_last_element(event.id),0));
					}
				}
				else{
					if(timedout[active_lengths.get_last_element(event.id)]){
						lengths[active_lengths.get_last_element(event.id)] += event.len - last_timeout[active_lengths.get_last_element(event.id)];
						timedout[active_lengths.get_last_element(event.id)] = 0;
						what_is_happening.insert(event_t(lengths[active_lengths.get_last_element(event.id)],active_lengths.get_last_element(event.id),0));
					}
				}
			}
			else{
				active_lengths.weight[active_lengths.get_root(event.id)];
			}

		}
	}

	for(int i = 1;i <= q;i++){
		fprintf(stdout,"%lld\n",ans[i]);
	}

    return 0;
}
