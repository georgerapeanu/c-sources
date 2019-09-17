#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

FILE *g = fopen("arb4.in","w");

const int NMAX = 3000;
const int MMAX = 7000;
const int CMAX = 1e9;

/*
const int NMAX = 20;
const int MMAX = 20;
const int CMAX = 100;
*/

int main() {

    random_device rd;
    mt19937 gen(rd());

    int n,m;

    n = gen() % NMAX + 1;
    m = gen() % MMAX + (n - 1);

    fprintf(g,"%d %d\n",n,m);

    set<int> costs;

    while((int)costs.size() < m) {
        costs.insert(gen() % CMAX + 1);
    }

    vector<int> v_costs;

    for(auto it:costs) {
        v_costs.push_back(it);
    }

    for(int i = 1; i < n; i++) {
        int id = gen() % int(v_costs.size());
        fprintf(g,"%d %d %d\n",i,int(gen() % i),v_costs[id]);
        swap(v_costs.back(),v_costs[id]);
        v_costs.pop_back();
    }

    for(int i = n; i <= m; i++) {
        int id = gen() % int(v_costs.size());
        fprintf(g,"%d %d %d\n",int(gen() % n),int(gen() % n),int(gen() % CMAX + 1));
        swap(v_costs.back(),v_costs[id]);
        v_costs.pop_back();
    }

    fclose(g);

    return 0;
}
