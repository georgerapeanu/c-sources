//gioto_bulaneala.cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;
constexpr int rad = 1000;

struct query {
	int l, r, pos;
};

inline void norm(vector <int> &a) {
	vector <int> b(a.size() + 1, 0);
	copy(a.begin(), a.end(), b.begin() + 1);

	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());

	for (auto &it : a)
		it = lower_bound(b.begin(), b.end(), it) - b.begin();
}


void solve(int n, int v[], int q, int l[], int r[], int solutions[]){
	vector <int> a(n);
	for (int i = 0; i < n ; ++i) {
		static int last = 0;

		a[i] = v[i] ^ last;
		last ^= v[i];
	}

	norm(a);

	vector <int> left(n + 1, -1); 
	for (int i = 0; i < n && i < rad ; ++i)
		left[a[i]] = i;
		
	for (int i = 0; i < q ; ++i) {
		--l[i];
		int ans = n + 1;
		for (int x = max(l[i] - rad, 0); x <= l[i] ; ++x)
			left[a[x]] = x;

		for (int y = r[i]; y < r[i] + rad && y < n ; ++y) {
			if (a[y] == 0)
				ans = min(ans, y + 1);

			if (left[a[y]] <= l[i] && left[a[y]] >= 0)
				ans = min(ans, y - left[a[y]]);
		}

		if (ans == n + 1)
			ans = -1;

		solutions[i] = ans;
	}

}


#include <stdio.h>
#include <stdlib.h>

#define LEN (1<<12)
static char buff[LEN];
static int ind = LEN - 1;

static int int32(){
  int ans = 0;

  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      fread(buff, 1, LEN, stdin);
      ind = 0;
    }
  }
  
  while(!(buff[ind] < '0' || buff[ind] > '9')){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      fread(buff, 1, LEN, stdin);
      ind = 0;
    }
  }
  return ans;
}

int main(){
  
  int n, q;
  n = int32();
  int* v = (int*)malloc(sizeof(int) * n);

  for(int i = 0;i < n;i++){
    v[i] = int32();
  }

  q = int32();

  int* l = (int*)malloc(sizeof(int) * q);
  int* r = (int*)malloc(sizeof(int) * q);
  for(int i = 0;i < q;i++){
    l[i] = int32();
    r[i] = int32();
  }

  int* answers = (int*)malloc(sizeof(int) * q);

  solve(n, v, q, l, r, answers);

  for(int i = 0;i < q;i++){
    printf("%d\n", answers[i]);
  }

  free(answers);
  free(l);
  free(r);
  free(v);

  return 0;
}
