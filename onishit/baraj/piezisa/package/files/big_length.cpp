#include "testlib.h"
#include <vector>

using namespace std;

const int QMAX = 5e5;

int main(int argc, char** argv){
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int vmax = opt<int>("vmax");

  printf("%d\n", n);
  for(int i = 1;i <= n;i++){
		static int now = 0;

		int x = rnd.next(0, vmax);
    printf("%d", x ^ now);
		now = x;

    if(i < n){
      printf(" ");
    }
  }
  printf("\n");

	vector <pair <int, int>> v;
	int q = 0;

	for (int l = n; l >= 1 && q < QMAX ; --l) for (int i = 0; i + l - 1 < n && q < QMAX ; ++i) {
		v.push_back({i, i + l - 1});
	    ++q;
	    
	}

	printf("%d\n", v.size());
	for (auto it : v)
		printf("%d %d\n", it.first, it.second);

	

  return 0;
}

