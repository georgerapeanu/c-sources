#include <cstdio>
#include <random>
#include <algorithm>

using namespace std;

FILE *g = fopen("niciomare.in","w");

const int NMAX = 1e4;
const int KMAX = 100;
const int SMAX = 1e5;

/*const int NMAX = 20;
const int KMAX = 5;
const int SMAX = 10;
*/
int main() {

    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    int k = gen() % NMAX + 1;
    int s = gen() % SMAX + 1;

    fprintf(g,"%d %d %d\n",n,k,s);

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",int(gen() % s + 1));
    }

    fclose(g);

    return 0;
}
