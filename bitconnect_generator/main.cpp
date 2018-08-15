#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>

using namespace std;

FILE *g = fopen("bitconnect.in","w");

const int NMAX = 500;
const int LGMAX = 62;
const long long VMAX = (1LL << (LGMAX));

set<long long> S;

long long aleg_random(){
    if(S.empty()){
        return -1;
    }
    int id = rand() % S.size();
    for(auto it:S){
        if(!id){
            return it;
        }
        id--;
    }
}

int main(){
	printf("%lld",RAND_MAX);
    srand(time(NULL));
    int N = rand() % NMAX;
    fprintf(g,"%d\n",N);

    while(N--){
        int t = rand() % 3 + 1;
        if(t == 3){
            long long x = aleg_random();
            long long y = aleg_random();
            if(x == -1){
                N++;
                continue;
            }
            if(y == -1){
                N++;
                continue;
            }
            fprintf(g,"%d %lld %lld\n",t,x,y);
        }
        else if(t == 2){
            long long x = aleg_random();
            if(x == -1){
                N++;
                continue;
            }
            S.erase(x);
            fprintf(g,"%d %lld\n",t,x);
        }
        else{
            long long x = rand() % VMAX;
            while(S.count(x)){
                x = rand() % VMAX;
            }
            S.insert(x);
            fprintf(g,"%d %lld\n",t,x);
        }
    }

    fclose(g);

    return 0;
}
