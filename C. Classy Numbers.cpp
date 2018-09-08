#include <cstdio>
#include <algorithm>

using namespace std;

int V[25];

long long get_sol(long long val) {
	long long rez = 0, cff = val;
	int len = 0;
	while (cff) {
		V[++len] = cff % 10;
		cff /= 10;
	}
	if (len <= 3){
		return val;
	}
	
	reverse(V + 1, V + len + 1);
	
	len--;
	
	rez += 9 * len;
	rez += 81 * len * (len - 1) / 2;
	rez += 729 * len * (len - 1) * (len - 2) / 6;
	
	rez++;
	
	rez += (V[1] - 1);
	rez += (V[1] - 1) * 9 * len;
	rez += (V[1] - 1) * 81 * len * (len - 1) / 2;
	
	int x = 2;
	int x1 = 1;
	while (x <= len + 1 && V[x] == 0){
		x++;
	}

	if (x > len + 1){
		return rez;
	}

	rez++;

	rez += (V[x] - 1);
	rez += (V[x] - 1) * 9 * (len + 1 - x);
	rez += (len + 1 - x) * 9;
	rez += (len + 1 - x) * (len - x) / 2 * 81;

	x++;

	while (x <= len + 1 && V[x] == 0){
		x++;
	}

	if (x <= len + 1){
		rez += V[x] + 9 * (len + 1 - x);
	}

	return rez;
}

int main() {

  int n;
  scanf("%d",&n);
  for (int i = 1; i <= n; ++i) {
    long long l, r;
    scanf("%I64d %I64d",&l,&r);
    printf("%I64d\n",get_sol(r) - get_sol(l - 1));
  }

  return 0;
}