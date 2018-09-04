#define JUDGE 1
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
 
using namespace std;
 
#if JUDGE
FILE *f = stdin;
FILE *g = stdout;
#else
FILE *f = fopen("robots.in","r");
FILE *g = fopen("robots.out","w");
#endif
int n,w,h;
int dp[505][505][50];
pair<int,int> where_do_i_end[505][505][4];
char C[505][505];
int sta[9][9],num;
 
const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};
const int inf = 1 << 28;
 
const int MAX_COST = 500 * 500;
 
vector< pair<int,int> > chestii[MAX_COST + 10];
 
int start_cost = inf;
int end_cost = 0;

inline int to_state(int x,int y){
	return sta[x][y];
}

inline void push(int x,int y,int cost){
    if(cost >= MAX_COST){
        return ;
    }
	chestii[cost].push_back({x,y});
	start_cost = min(start_cost,cost);
	end_cost = max(end_cost,cost);
}
 
void solve(int state){
	for(int cost = start_cost;cost <= end_cost;cost++){
		for(auto pos:chestii[cost]){
			if(dp[pos.first][pos.second][state] != cost){
				continue;
			}
			for(int k = 0;k < 4;k++){
				pair<int,int> npos = where_do_i_end[pos.first][pos.second][k];
				if(npos.first == -1 && npos.second == -1){
					continue;
				}
 
				if(dp[npos.first][npos.second][state] > cost + 1){
					dp[npos.first][npos.second][state] = cost + 1;
					push(npos.first,npos.second,cost + 1);
				}
			}
		}
		chestii[cost].clear();
	}
	start_cost = inf;
	end_cost = 0;
}
 
int which_viz[505][505][4];
int last_viz;
 
pair<int,int> get_end(int i,int j,int k){
	if(where_do_i_end[i][j][k].first || where_do_i_end[i][j][k].second){
		return where_do_i_end[i][j][k];
	}
 
	if(C[i][j] == 'x'){
		where_do_i_end[i][j][k] = {-1,-1};
		return {-1,-1};
	}
 
	where_do_i_end[i][j][k] = {i,j};
 
	vector< pair<pair<int,int>,int> > V = {make_pair(make_pair(i,j),k)};
	which_viz[i][j][k] = ++last_viz;
 
	pair<int,int> ans = {-1,-1};
 
 
	for(int k = 0;k < (int)V.size();k++){
		int dir = (V[k].second + (C[V[k].first.first][V[k].first.second] == 'C') + (C[V[k].first.first][V[k].first.second] == 'A' ? 3:0)) & 3;
		int x = V[k].first.first + dx[dir];
		int y = V[k].first.second + dy[dir];
 
		if(!(x && y && x <= h && y <= w && C[x][y] != 'x')){
			ans = V[k].first;
			break;
		}
 
		else if(!which_viz[x][y][dir]){
			V.push_back({{x,y},dir});
			which_viz[x][y][dir] = last_viz;
		}
 
		else{
			if(which_viz[x][y][dir] != last_viz){
				ans = where_do_i_end[x][y][dir];
			}
			else{
				break;
			}
		}
	}
 
	for(auto it:V){
		where_do_i_end[it.first.first][it.first.second][it.second] = ans;
	}
 
	return where_do_i_end[i][j][k];
}
 
int main(){
	fscanf(f,"%d %d %d\n",&n,&w,&h);
	
	for(int i = 0;i < n;i++){
		for(int j = i;j < n;j++){
			sta[i][j] = num++;
		}
	}
 
	for(int i = 1;i <= h;i++){
		fgets(C[i] + 1,505,f);
	}
 
 
	for(int i = 1;i <= h;i++ ){
		for(int j = 1;j <= w;j++){
			for(int k = 0;k < 4;k++){
				where_do_i_end[i][j][k] = get_end(i,j,k);
			}
		}
	}
 
	for(int i = 1;i <= h;i++){
		for(int j = 1;j <= w;j++){
			for(int st = 0;st < 50;st++){
					dp[i][j][st] = inf;
			}
		}
	}
	for(int i = 1;i <= h;i++){
		for(int j = 1;j <= w;j++){
			if('1' <= C[i][j] && C[i][j]  <= '9'){
				dp[i][j][to_state(C[i][j] - '1',C[i][j] - '1')] = 0;
				push(i,j,0);
				solve(to_state(C[i][j] - '1',C[i][j] - '1'));
			}
		}
	}
	for(int l = 1;l < 9;l++){
		for(int st = 0;st < n - l;st++){
			int dr = st + l;
			int state = to_state(st,dr);
			for(int i = 1;i <= h;i++){
				for(int j = 1;j <= w;j++){
						for(int k = st;k < dr;k++){
							dp[i][j][state] = min(dp[i][j][to_state(st,k)] + dp[i][j][to_state(k + 1,dr)],dp[i][j][state]);
						}
						push(i,j,dp[i][j][state]);
				}
			}
			solve(state);
		}
	}
 
	int ans = inf;
	int state = to_state(0,n - 1);
	
	for(int i = 1;i <= h;i++){
		for(int j = 1;j <= w;j++){
			if(ans > dp[i][j][state]){
				ans = dp[i][j][state];
			}
		}
	}
 
	fprintf(g,"%d\n",(ans == inf ? -1:ans));
 
	return 0;
}