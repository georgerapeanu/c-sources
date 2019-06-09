#include <cstdio>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;

FILE *g = fopen("comp.in","w");

const int NMAX = 16000;
vector<pair<int,int> > nodes;

int main(){
    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;

    nodes.push_back({1,0});

    fprintf(g,"%d\n",n);

    for(int i = 2;i <= n;i++){
        int ind = gen() % ((int)nodes.size());
        swap(nodes[ind],nodes.back());
        fprintf(g,"%d %d\n",i,nodes.back().first);
        nodes.back().second++;
        if(nodes.back().second == 2){
            nodes.pop_back();
        }
        nodes.push_back({i,0});
    }

    fclose(g);

    return 0;
}
