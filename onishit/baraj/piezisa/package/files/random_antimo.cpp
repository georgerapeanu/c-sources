#include "testlib.h"

using namespace std;

int main(int argc, char** argv){
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int vmax = opt<int>("vmax");

  printf("%d\n", n);
  for(int i = 1;i <= n;i++){
    printf("%d", rnd.next(0, vmax));
    if(i < n){
      printf(" ");
    }
  }
  printf("\n");

int q = 5e5;
  printf("%d\n", q);

	for (int i = 0; i < n - 1 && q > 0 ; ++i) {
		printf("%d %d\n", i, i + 1);
		--q;
	}

	while (q > 0) {
		for (int i = 1; i < n && q > 0 ; ++i) {
			printf("%d %d\n", i, rnd.next(i, n - 1));
			--q;
		}
	}

  return 0;
}
