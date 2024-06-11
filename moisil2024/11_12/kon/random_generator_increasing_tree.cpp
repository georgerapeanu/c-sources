#include <testlib.h>

using namespace std;

int main(int argc, char** argv) {
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int k = opt<int>("k");
  int vmax = opt<int>("vmax");

  cout << n << " " << k << endl;
  
  for(int i = 1;i <= n;i++){
    cout << rnd.next(0, vmax);
    if(i < n){
      cout << " ";
    }
  }

  cout << endl;

  for(int i = 2;i <= n;i++){
    cout << i << " " << rnd.next(1, i - 1) << endl;
  }


  return 0;
}

