#include <cstdio>
#include <vector>

using namespace std;

FILE *f = fopen("prim.in","r");
FILE *g = fopen("prim.out","w");

int K;
const int LIM = 2000000;
vector<int> primes;
bool E[LIM];
int main(){
    fscanf(f,"%d",&K);

    E[0] = E[1] = 1;
    for(int i = 2;1LL * i * i < LIM;i++){
        if(!E[i]){
            for(int j = i * i;j < LIM;j += i){
                E[j] = 1;
            }
        }
    }

    for(int i = 2;i < LIM;i++){
        if(!E[i]){
            primes.push_back(i);
        }
    }

    fprintf(g,"%lld",1LL * primes[K] * primes[K]);

    fclose(f);
    fclose(g);

    return 0;
}
