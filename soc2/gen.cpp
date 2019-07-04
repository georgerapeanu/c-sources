#include <cstdio>
#include <algorithm>
#include <random>
#include <set>
#include <vector>

using namespace std;

const int NMAX = 25;
const int VMAX = 1e6;

FILE *g = fopen("soc2.in","w");

int main() {

    random_device rd;
    mt19937 gen(rd());

    int n = gen() % NMAX + 1;
    set<pair<int,int> > edges;
    vector<int> verticies = {1};

    for(int i = 2; i <= n; i++) {
        random_shuffle(verticies.begin(),verticies.end());
        int target = gen() % (int)verticies.size();///at most untill target
        int pref = 0;

        for(pref = 0;pref <= target;pref++){
            bool ok = true;
            for(int j = 0;j < pref;j++){
                if(edges.count({verticies[j],verticies[pref]}) || edges.count({verticies[pref],verticies[j]})){
                }
                else{
                    ok = false;
                }
            }
            if(ok == false){
                target = pref - 1;
                break;
            }
        }

        for(int j = 0;j <= target;j++){
            edges.insert({i,verticies[j]});
        }
        
        verticies.push_back(i);
    }

    fprintf(g,"%d %d\n",n,(int)edges.size());

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",int(gen() % VMAX + 1));
    }
    fprintf(g,"\n");

    for(auto it:edges) {
        fprintf(g,"%d %d\n",it.first,it.second);
    }

    fclose(g);

    return 0;
}
