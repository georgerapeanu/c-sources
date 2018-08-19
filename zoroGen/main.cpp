#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
FILE *g = fopen("zoro.in","w");
const int NMAX = 200;
vector<int> V;
int main()
{
    srand(time(NULL));
    int N = rand() % NMAX + 1;
    int M = rand() % NMAX + 1;
    fprintf(g,"%d %d\n",N,M);
    for(int i = 1;i <= N * M;i++){
        V.push_back(i);
    }
    random_shuffle(V.begin(),V.end());
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            fprintf(g,"%d ",V[(i - 1) * M + j - 1]);
        }
        fprintf(g,"\n");
    }
    fclose(g);
    return 0;
}
