#include <bits/stdc++.h>
	
 
	
const int MAX_N = 100000;
	
const int MOD = 1000000007;
	
 
	
int father[MAX_N];
	
long long d[MAX_N];
	
std::vector<int> graph[MAX_N];
	
 
	
int subtree[MAX_N], depth[MAX_N];
	
 
	
void calc_statistics(int nod) {
	
	subtree[nod] = 1;
	
	for(auto it: graph[nod]) {
	
		depth[it] = depth[nod] + 1;
	
		calc_statistics(it);
	
		subtree[nod] += subtree[it];
	
	}
	
}
	
 
	
int last_id;
	
int heavy_id[MAX_N], heavy_head[MAX_N], traversal[1+MAX_N];
	
 
	
void heavy_traversal(int nod, int my_root) {
	
	heavy_id[nod] = ++last_id;
	
	traversal[last_id] = nod;
	
	heavy_head[nod] = my_root;
	
 
	
	int heavy_son = -1;
	
	for(auto it: graph[nod])
	
		if(heavy_son == -1 || (heavy_son != -1 && subtree[it] > subtree[heavy_son]))
	
			heavy_son = it;
	
	
	
	if(heavy_son != -1) {
	
		heavy_traversal(heavy_son, my_root);
	
		for(auto it: graph[nod])
	
			if(it != heavy_son)
	
				heavy_traversal(it, it);
	
	}
	
}
	
 
	
int aint[1+4*MAX_N];
	
 
	
void mark_aint(int pos, int val, int l = 1, int r = MAX_N, int nod = 1) {
	
	if(pos < l || r < pos) return;
	
 
	
	if(l == r)
	
		aint[nod] = val;
	
	else {
	
		int mid = (l + r) / 2;
	
		mark_aint(pos, val, l, mid, 2 * nod);
	
		mark_aint(pos, val, mid + 1, r, 2 * nod + 1);
	
		aint[nod] = std::max(aint[2 * nod], aint[2 * nod + 1]);
	
	}
	
}
	
 
	
int get_marked(int i, int j, int l = 1, int r = MAX_N, int nod = 1) {
	
	if(j < l || r < i || j < i) return 0;
	
 
	
	if(i <= l && r <= j)
	
		return aint[nod];
	
	else {
	
		int mid = (l + r) / 2;
	
		return std::max(get_marked(i, j, l, mid, 2 * nod),
	
		                get_marked(i, j, mid + 1, r, 2 * nod + 1));
	
	}
	
}
	
 
	
long long aib[1+MAX_N];
	
 
	
static inline int lsb(int x) {
	
	return x & (-x);
	
}
	
 
	
void update_aib(int pos, long long val) {
	
	while(pos <= MAX_N) {
	
		aib[pos] += val;
	
		pos += lsb(pos);
	
	}
	
}
	
 
	
long long query(int pos) {
	
	long long res = 0LL;
	
	while(pos > 0) {
	
		res += aib[pos];
	
		pos -= lsb(pos);
	
	}
	
	return res;
	
}
	
 
	
int final_sum;
	
 
	
void add_range(int l, int r, long long val) {
	
	update_aib(l, val);
	
	update_aib(r + 1, -val);
	
	final_sum = (val % MOD * (r - l + 1) + final_sum) % MOD;
	
}
	
 
	
long long get_down_chain(int nod) {
	
	return query(heavy_id[nod]);
	
}
	
 
	
long long cached_dp[MAX_N];
	
int chosen[MAX_N][3];
	
 
	
bool cmp_chosen(int a, int b) {
	
	return cached_dp[a] > cached_dp[b];
	
}
	
 
	
int last_sons;
	
// Returns the difference between the old dp and the new dp
	
long long get_addition(int nod, int from) {
	
	int sons = std::min(2, (int)graph[nod].size());
	
	cached_dp[nod] = get_down_chain(nod);
	
	bool found = false;
	
 
	
	for(int i = 0; i < sons; ++i) {
	
		cached_dp[chosen[nod][i]] = get_down_chain(chosen[nod][i]) + d[chosen[nod][i]];
	
		if(chosen[nod][i] == from)
	
			found = true;
	
	}
	
 
	
	if(!found) {
	
		cached_dp[from] = (get_down_chain(from) + d[from]);
	
		chosen[nod][sons++] = from;
	
	}
	
 
	
	std::sort(chosen[nod], chosen[nod] + sons, cmp_chosen);
	
	last_sons = sons;
	
	if(sons == 0) return 0;
	
	return cached_dp[chosen[nod][0]] - cached_dp[nod];
	
}
	
 
	
void mark_node(int nod) {
	
	mark_aint(heavy_id[nod], heavy_id[nod]);
	
}
	
 
	
int get_marked_above(int nod) {
	
	return traversal[get_marked(heavy_id[heavy_head[nod]], heavy_id[nod])];
	
}
	
 
	
void get_initial_partition(int nod) {
	
	for(auto it: graph[nod])
	
		get_initial_partition(it);
	
 
	
	for(int i = 0; i < 3; ++i)
	
		chosen[nod][i] = -1;
	
 
	
	if(graph[nod].size() >= 1)
	
		chosen[nod][0] = graph[nod][0];
	
	if(graph[nod].size() >= 2)
	
		chosen[nod][1] = graph[nod][1];
	
	
	
	long long dp = 0LL;
	
	for(auto it: graph[nod])
	
		dp = get_addition(nod, it);
	
	
	
	if(graph[nod].size() >= 2)
	
		final_sum = (final_sum + cached_dp[chosen[nod][1]]) % MOD;
	
	add_range(heavy_id[nod], heavy_id[nod], dp);
	
 
	
	for(auto it: graph[nod])
	
		if(it != chosen[nod][0])
	
			mark_node(it);
	
}
	
 
	
int main() {
	
	int N;
	
	FILE *fin = fopen("arboras.in", "r");
	
	FILE *fout = fopen("arboras.ok", "w");
	
 
	
	fscanf(fin, "%d", &N);
	
	father[0] = -1;
	
	for(int i = 1; i < N; ++i) {
	
		fscanf(fin, "%d", &father[i]);
	
		graph[father[i]].push_back(i);
	
	}
	
	for(int i = 1; i < N; ++i)
	
		fscanf(fin, "%lld", &d[i]);
	
 
	
	calc_statistics(0);
	
	heavy_traversal(0, 0);
	
	get_initial_partition(0);
	
 
	
	fprintf(fout, "%d\n", final_sum);
	
	
	
	int Q;
	
	fscanf(fin, "%d", &Q);
	
	while(Q--) {
	
		int nod;
	
		long long add, prevadd;
	
		fscanf(fin, "%d%lld", &nod, &add);
	
		d[nod] += add;
	
		do {
	
			int mark = get_marked_above(nod);
	
			if(mark == 0) { // Increase the whole chain and move on
	
				add_range(heavy_id[heavy_head[nod]], heavy_id[nod] - 1, add);
	
				nod = father[heavy_head[nod]];
	
				if(nod != -1)
	
					add_range(heavy_id[nod], heavy_id[nod], add);
	
			} else { // father[mark] must be recalculated from mark
	
				int f = father[mark];
	
				add_range(heavy_id[mark], heavy_id[nod] - 1, add);
	
 
	
				for(int i = 0; i < std::min(2, (int)graph[f].size()); ++i) {
	
					mark_node(chosen[f][i]);
	
				}
	
				
	
				prevadd = add;
	
				add = get_addition(f, mark);
	
				if(last_sons == 2) {
	
					add_range(heavy_id[f], heavy_id[f], add);
	
					final_sum = (final_sum + prevadd - add) % MOD;
	
				} else if(last_sons == 3 && (mark == chosen[f][0] ||
	
				                             mark == chosen[f][1])) {
	
					add_range(heavy_id[f], heavy_id[f], add);
	
					long long to_add = 0LL;
	
					if(mark == chosen[f][0])
	
						to_add = cached_dp[chosen[f][0]];
	
					else
	
						to_add = cached_dp[chosen[f][1]];
	
					to_add -= cached_dp[chosen[f][2]];
	
					final_sum = (final_sum + (to_add - add)) % MOD;
	
				}
	
				
	
				if(last_sons >= 1) {
	
					mark_aint(heavy_id[chosen[f][0]], 0);
	
				}
	
				if(last_sons >= 2 && chosen[f][0] != mark)
	
					add = 0;
	
 
	
				nod = f;
	
			}
	
		} while(nod != -1 && father[nod] != -1 && add > 0LL);
	
 
	
		fprintf(fout, "%d\n", final_sum);
	
	}
	
 
	
	fclose(fin);
	
	fclose(fout);
	
	return 0;
	
}
