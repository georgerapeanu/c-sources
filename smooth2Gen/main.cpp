#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
FILE *g = fopen("smooth2.in","w");
int N;
const int NMAX = 100;
int main(){
    srand(time(NULL));
    N = rand() % NMAX + 1;
    for(int i = 1;i <= N;i++){
        fprintf(g,"%c",rand() % 26 + 'a');
    }
    fclose(g);
    return 0;
}
