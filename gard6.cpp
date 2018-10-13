#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <stdexcept>
 
using namespace std;
 
FILE *f = fopen("gard6.in","r");
FILE *g = fopen("gard6.out","w");
 
///tested on infoarena.ro/problema/harbingers 
///insert only if next a < all inserted a's in the current version
///compress tells the structure if it is needed to maintain all versions or if we can dump one once we undo it,this affect checkout
class InsertUndoMinConvexHull{
  
private:
  
	bool compress;
    const double EPS = 1e-6;
	
    int head;
    vector<int> prev_state;
    vector<double> sect_with_ant;
    vector<int> prev_line;
    vector<int> lvl;
    vector< pair<long long,long long> > segment;
    vector< vector<int> > father;
  
  
    ///tells if the segment at position pos is completly covered by inserting a new line
    bool bad(int pos,pair<long long,long long> line){
        if(pos <= 1){
            return false;
        }
   
        if(sect_with_ant[pos] - ((double)line.second - segment[prev_line[pos]].second) /  (segment[prev_line[pos]].first - line.first) > -EPS){
            return true;
        }
   
        return false;
    }
     
    ///tells if x is on the left part of the join between this and previous line
    bool on_the_left(int pos,int x){
        if(pos <= 1){
            return false;
        }
          
        if(sect_with_ant[pos] - x > -EPS){
            return true;
        }
          
        return false;
    }
public:
  
    InsertUndoMinConvexHull(bool compress = false){
        this->head = 0;
        this->prev_state = vector<int>(1,0);
        this->prev_line = vector<int>(1,0);
        this->lvl = vector<int>(1,0);
        this->sect_with_ant = vector<double>(1,0);
        this->segment = vector< pair<long long,long long> >(1,make_pair(0,0));
        this->father = vector< vector<int> >(1,vector<int>());
		this->compress = compress;
  
    }
  
    void add(pair<long long,long long> line){
        if(head && segment[head].first <= line.first){
            throw runtime_error("the slope inserted is not smaller than the current smallest one");
        }
		
		int new_head;
		
		if(compress){
			new_head = head + 1;
			
			if(new_head >= (int)prev_state.size()){
				prev_state.push_back(head);
				prev_line.push_back(0);
				lvl.push_back(0);
				segment.push_back(line);
				father.push_back(vector<int>());
				sect_with_ant.push_back(0);
			}
			else{
				prev_state[new_head] = head;
				prev_line[new_head] = 0;
				lvl[new_head] = 0;
				segment[new_head] = line;
				father[new_head] = vector<int>();
				sect_with_ant[new_head] = 0;
			}
			 
		}
		
		else{
			new_head = prev_state.size();
			prev_state.push_back(head);
			prev_line.push_back(0);
			lvl.push_back(0);
			segment.push_back(line);
			father.push_back(vector<int>());
			sect_with_ant.push_back(0);
		}
 
		for(int step = (int)father[head].size() - 1;step >= 0;step--){
			if(step < (int)father[head].size() && father[head][step] && bad(father[head][step],line)){
				head = father[head][step];
			}
		}
  
        if(bad(head,line)){
            prev_line[new_head] = prev_line[head];
            lvl[new_head] = lvl[prev_line[head]] + 1;
        }
  
        else{
            prev_line[new_head] = head;
            lvl[new_head] = lvl[head] + 1;
        }
        head = new_head;
  
        father[head].push_back(prev_line[head]);
  
        if(prev_line[head]){
            sect_with_ant[head] = ((double)segment[head].second - segment[prev_line[head]].second) / (segment[prev_line[head]].first - segment[head].first);
        }
  
        for(int step = 1;(1 << step) <= (int)lvl[head];step++){
            father[head].push_back(father[father[head][step - 1]][step - 1]);
        }
    }
  
    long long query(int x){
        int where = head;
        for(int step = (int)father[where].size() - 1;step >= 0;step--){
            if(step < (int)father[where].size() && on_the_left(father[where][step],x)){
                where = father[where][step];
            }
        }
  
        if(on_the_left(where,x)){
            where = prev_line[where];
        }
  
        return 1LL * x * segment[where].first + segment[where].second;
    }
  
    void undo(){
        if(head == 0){
            throw runtime_error("empty hull");
        }
        head = prev_state[head];
    }
	
	void checkout(int version){
		if(compress){
			throw runtime_error("tried to checkout with compression on");
		}
		head = version;
	}
  
    void print_current(){
        vector< pair<long long,long long> > to_print;
        int tmp_head = head;
        while(tmp_head){
            to_print.push_back(segment[tmp_head]);
            tmp_head = prev_line[tmp_head];
        }
  
        reverse(to_print.begin(),to_print.end());
  
        for(auto it:to_print){
            printf("%lld %lld\n",it.first,it.second);
        }
        printf("\n\n\n");
    }
};
 
 
struct linear_convex_hull_line_t{
	long long a,b;
	int id;
	
	linear_convex_hull_line_t(long long a,long long b,int id){
		this->a = a;
		this->b = b;
		this->id = id;
	}
	
	double sect(linear_convex_hull_line_t &other){
		if(other.a == this->a){
			throw runtime_error("intersection of parallel lines is required");
		}
		return ((double)other.b - this->b) / (this->a - other.a);
	}
	
	long long operator ()(int x){
		return 1LL * a * x + b;
	}
};
 
///supports only addition to the extremes
class LinearMinConvexHull{
 
private:
	
	const double EPS = 1e-6;
	deque<double> sect_with_ant;
	deque<double> sect_with_nxt;
	
public:
 
	deque< linear_convex_hull_line_t > segment;
 
	LinearMinConvexHull(){
		segment = deque< linear_convex_hull_line_t >();
		sect_with_ant = deque< double >();
		sect_with_nxt = deque< double >();
	}
	
	void add_front(linear_convex_hull_line_t line){
		if(!segment.empty() && line.a <=  segment.front().a){
			throw runtime_error("tried to insert to front with smaller slope");
		}
		
		if(segment.size() == 0){
			segment.push_back(line);
			sect_with_ant.push_front(0);
			sect_with_nxt.push_front(0);
			return ;
		}
		
		while((int)segment.size() >= 2 && (line.sect(segment[1]) - sect_with_nxt[0] > -EPS)){
			segment.pop_front();
			sect_with_nxt.pop_front();
			sect_with_ant.pop_front();
			sect_with_ant[0] = 0;
		}
		
		segment.push_front(line);
		sect_with_nxt.push_front(segment[0].sect(segment[1]));
		sect_with_ant[0] = segment[0].sect(segment[1]);
		sect_with_ant.push_front(0);
	}
	
	void add_back(linear_convex_hull_line_t line){
		if(!segment.empty() && line.a >=  segment.back().a){
			throw runtime_error("tried to insert to back with bigger slope");
		}
		
		if(segment.size() == 0){
			segment.push_back(line);
			sect_with_ant.push_back(0);
			sect_with_nxt.push_back(0);
			return ;
		}
		
		while((int)segment.size() >= 2 && sect_with_ant.back() - line.sect(segment[(int)segment.size() - 2]) >= -EPS){
			  segment.pop_back();
			  sect_with_ant.pop_back();
			  sect_with_nxt.pop_back();
			  sect_with_nxt.back() = 0;
		}
		
		segment.push_back(line);
		sect_with_nxt.back() = segment[(int)segment.size() - 2].sect(segment[(int)segment.size() - 1]);
		sect_with_nxt.push_back(0);
		sect_with_ant.push_back(segment[(int)segment.size() - 2].sect(segment[(int)segment.size() - 1]));
			  
	}
	
	linear_convex_hull_line_t query(int x){
		
		if(segment.size() == 0){
			throw runtime_error("hull empty");
		}
		
		if(segment.size() == 1){
			return segment[0];
		}
		
		if(sect_with_nxt[0] - x >= -EPS){
			return segment[0];
		}
		
		int st = 0,dr = (int)segment.size() - 1;
		
		while(dr - st > 1){
			int mid = (st + dr) / 2;
			
			if(sect_with_nxt[mid] - x <= EPS){
				st = mid;
			}
			
			else{
				dr = mid;
			}
		}
		
		return segment[dr];
	}
	
	inline int sz(){
		return segment.size();
	}
	
	void swap_with(LinearMinConvexHull &other){
		this->segment.swap(other.segment);
		this->sect_with_ant.swap(other.sect_with_ant);
		this->sect_with_nxt.swap(other.sect_with_nxt);
	}
	
	void del(){
		segment.clear();
		sect_with_ant.clear();
		sect_with_nxt.clear();
	}
};
 
///merges a with b and outputs result to a
void linear_hull_merge(LinearMinConvexHull &a,LinearMinConvexHull &b){
	if(a.sz() >= b.sz()){
		for(auto it:b.segment){
			a.add_back(it);
		}
	}
	
	else{
		reverse(a.segment.begin(),a.segment.end());
		for(auto it:a.segment){
			b.add_front(it);
		}
		a.swap_with(b);
	}
}
 
const int NMAX = 1e5;
 
int n,k;
vector< vector<long long> > dp;
int v[NMAX + 5];
int st[NMAX + 5],len;
LinearMinConvexHull hulls[NMAX + 5];
 
int main(){
	
	fscanf(f,"%d %d",&n,&k);
	
	for(int i = 1;i <= n;i++){
		fscanf(f,"%d",&v[i]);
	}
	
	dp = vector< vector<long long> > (k + 1,vector<long long>(n + 1,0LL));
 
	int ma = 0;
	
	for(int i = 1;i <= n;i++){
		ma = max(ma,v[i]);
		dp[1][i] = 1LL * ma * i;
	}
	
	for(int i = 2;i <= k;i++){
		len = 0;
		InsertUndoMinConvexHull major_hull(true);
		for(int j = 1;j <= n;j++){
			st[++len] = j;
			hulls[len].del();
			hulls[len].add_back(linear_convex_hull_line_t(-(j - 1),dp[i - 1][j - 1],j - 1));
			while(len > 1 && v[st[len - 1]] <= v[st[len]]){
				st[len - 1] = st[len];
				linear_hull_merge(hulls[len - 1],hulls[len]);
				len--;
				major_hull.undo();
			}
			
			int id = hulls[len].query(v[st[len]]).id;
			long long b = dp[i - 1][id]	- 1LL * v[st[len]] * id;
			long long a = v[st[len]];
			major_hull.add(make_pair(a,b));
			
			dp[i][j] = major_hull.query(j);
			
		}
	}
	
	fprintf(g,"%lld",dp[k][n]);
	
	fclose(f);
	fclose(g);
	
	return 0;
}