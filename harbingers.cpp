#include <cstdio>
#include <algorithm>
#include <vector>
#include <stdexcept>
 
using namespace std;
 
FILE *f = fopen("harbingers.in","r");
FILE *g = fopen("harbingers.out","w");
 
///insert only if next a < all inserted a's in the current version
class InsertUndoMinConvexHull{
 
private:
 
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
 
    InsertUndoMinConvexHull(){
        head = 0;
        prev_state = vector<int>(1,0);
        prev_line = vector<int>(1,0);
        lvl = vector<int>(1,0);
        sect_with_ant = vector<double>(1,0);
        segment = vector< pair<long long,long long> >(1,make_pair(0,0));
        father = vector< vector<int> >(1,vector<int>());
 
    }
 
    void add(pair<long long,long long> line){
        if(head && segment[head].first <= line.first){
            throw runtime_error("the slope inserted is not smaller than the current smallest one");
        }
 
        prev_state.push_back(head);
        prev_line.push_back(0);
        lvl.push_back(0);
        segment.push_back(line);
        father.push_back(vector<int>());
		sect_with_ant.push_back(0);
		
        for(int step = (int)father[head].size() - 1;step >= 0;step--){
            if(step < (int)father[head].size() && father[head][step] && bad(father[head][step],line)){
                head = father[head][step];
            }
        }
 
 
        if(bad(head,line)){
            prev_line.back() = prev_line[head];
            lvl.back() = lvl[prev_line[head]] + 1;
        }
 
        else{
            prev_line.back() = head;
            lvl.back() = lvl[head] + 1;
        }
        head = (int)prev_state.size() - 1;
 
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
 
    void print_current(){
        vector< pair<long long,long long> > to_print;
        int tmp_head = head;
        while(tmp_head){
            to_print.push_back(segment[tmp_head]);
            tmp_head = prev_line[tmp_head];
        }
 
        reverse(to_print.begin(),to_print.end());
 
        for(auto it:to_print){
            printf("%d %d\n",it.first,it.second);
        }
        printf("\n\n\n");
    }
};
 
const int NMAX = 1e5;
 
int n;
int sum[NMAX + 5];
long long dp[NMAX + 5];
pair<int,int> mess[NMAX + 5];
vector< pair<int,int> > graph[NMAX + 5];
 
void dfs(int nod,int tata,InsertUndoMinConvexHull &hull){
 
    if(tata != 0){
        dp[nod] = hull.query(mess[nod].first) + 1LL * sum[nod] * mess[nod].first + mess[nod].second;
    }
    hull.add({-sum[nod],dp[nod]});
 
    for(auto it:graph[nod]){
        if(it.first != tata){
            sum[it.first] = sum[nod] + it.second;
            dfs(it.first,nod,hull);
        }
    }
 
    hull.undo();
}
 
const int LEN = 1 << 13;
char buff[LEN];
int ind = LEN - 1;

int i32(){
	int ans = 0;
	
	while(buff[ind] < '0' || buff[ind] > '9'){
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	
	while(buff[ind] >= '0' && buff[ind] <= '9'){
		ans = ans * 10 + (buff[ind] - '0');
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,f);
		}
	}
	return ans;
}
 
int main(){
    n = i32();
 
    for(int i = 2;i <= n;i++){
        int x,y,v;
        x = i32();y = i32();v = i32();
        graph[x].push_back({y,v});
        graph[y].push_back({x,v});
    }
 
    for(int i = 2;i <= n;i++){
        mess[i].second = i32();mess[i].first = i32();
    }
 
    InsertUndoMinConvexHull hull;
 
    dfs(1,0,hull);
 
    for(int i = 2;i <= n;i++){
        fprintf(g,"%lld ",dp[i]);
    }
 
    fclose(f);
    fclose(g);
 
    return 0;
}