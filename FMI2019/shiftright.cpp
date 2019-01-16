#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

ifstream f("shiftright.in");
ofstream g("shiftright.out");

const int SIGMA = 26;
const int NMAX = 1e5;

set<int> pos[SIGMA];

int link[NMAX + 5];
bool viz[NMAX + 5];

int main() {

    string init,req;
    vector<int> fr(SIGMA,0);

    f >> init >> req;

    int last = 0;
    int n = init.size();

    for(auto it:init) {
        fr[it - 'a']++;
    }
    last++;
    last = 0;
    for(auto it:req) {
        fr[it - 'a']--;
        if(init[last] != req[last]) {
            pos[it - 'a'].insert(last);
        }
        last++;
    }

    for(auto it:fr){
        if(it != 0) {
            g << -1;
            return 0;
        }
    }

    for(int i = 0; i < n; i++) {
        if(init[i] == req[i]) {
            link[i] = -1;
            viz[i] = true;
            continue;
        }
        set<int> :: iterator it = pos[init[i] - 'a'].lower_bound(i);
        if(it == pos[init[i] - 'a'].end()) {
            it = pos[init[i] - 'a'].begin();
        }
        link[i] = *it;
        pos[init[i] - 'a'].erase(it);
    }


    vector< vector<int> > op;

    for(int i = 0; i < n; i++) {
        if(!viz[i]) {
            vector<int> cycle;

            for(int nod = i; !viz[nod]; nod = link[nod]) {
                viz[nod] = true;
                cycle.push_back(nod);
            }

            vector<int> curr;

            for(int i = 0; i < (int)cycle.size(); i++) {
                curr.push_back(cycle[i]);
                if(i == (int)cycle.size() - 1 || cycle[i + 1] < cycle[i]) {
                    op.push_back(curr);
                    while(curr.size() > 1) {
                        curr.pop_back();
                    }
                }
            }
        }
    }

    g << op.size() << "\n";

    for(auto it:op) {
        g << it.size() << " ";
        for(auto it2:it) {
            g << it2 << " ";
        }
        g << "\n";
    }

    return 0;
}

