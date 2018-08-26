#include <bits/stdc++.h>

using namespace std;

int NMAX = 500;
int KMAX = 6;

vector<int>G[505];
int col[505];

int parse(string &a){
	int ans = 0;
	for(auto it:a){
		ans = ans * 10 + it - '0';
	}
	return ans;
}

int main(int argc,char **argv) {
 
	for(int i = 1;i < argc;i++){
		string tmp = argv[i];
		if(tmp == "NMAX"){
			string a = argv[++i];
			NMAX = parse(a);
		}
		else if(tmp == "KMAX"){
			string a = argv[++i];
			KMAX = parse(a);
		}
		else{
			throw runtime_error("invalid arguments");
		}
	}
 
 freopen("design.in", "w", stdout);

  srand(time(NULL));

  int n, k;
  n = rand() % NMAX + 1;
  k = rand() % min(KMAX, 500 / n) + 1;
  printf("%d %d\n", n, k);
  for (int i = 2; i <= n; ++i) {
    int x = rand() % (i - 1) + 1;
    G[i].push_back(x);
    G[x].push_back(i);
  }
  for (int i = 1; i <= n; ++i)
    col[i] = rand() % k + 1;
  for (int i = 1; i <= n; ++i) {
    printf("%d\n", G[i].size());
    for (auto it:G[i])
      printf("%d ", col[it]);
    printf("\n");
    for (auto it:G[i])
      printf("%d ", it);
  }

  return 0;
}