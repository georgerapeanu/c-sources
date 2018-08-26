#include <bits/stdc++.h>

using namespace std;

struct Muc {
  int a, b, c;
  bool operator < (const Muc& other) const {
    return c < other.c;
  }
}m[100005];

int NMAX = 1e5;
int VMAX = 1000000000;

int parse(string &a){
	int ans = 0;
	for(auto it:a){
		ans = ans * 10 + it - '0';
	}
	return ans;
}

int main(int argc,char **argv){

	for(int i = 1;i < argc;i++){
		string tmp = argv[i];
		if(tmp == "NMAX"){
			string a = argv[++i];
			NMAX = parse(a);
		}
		else if(tmp == "VMAX"){
			string a = argv[++i];
			VMAX = parse(a);
		}
		else{
			throw runtime_error("invalid arguments");
		}
	}


  freopen("nespus.in", "w", stdout);

  srand(time(NULL));

  int n, k;
  n = rand() % (NMAX - 1) + 2;
  k = rand() % (n - 1) + 2;
  printf("%d %d\n", n, k);
  for (int i = 2; i <= n; ++i) {
    int x = rand() % (i - 1) + 1;
    m[i].a = i;
    m[i].b = x;
    m[i].c = rand() % VMAX + 1;
  }

  sort(m + 2, m + n + 1);
  for (int i = 2; i <= n; ++i)
    printf("%d %d %d\n", m[i].a, m[i].b, m[i].c);

  return 0;
}