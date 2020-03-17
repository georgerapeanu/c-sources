#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

FILE *f = fopen("steeplechase.in","r");
FILE *g = fopen("steeplechase.out","w");

const int NMAX = 250;

int n;
int x[NMAX + 5];
int y[NMAX + 5];
int xx[NMAX + 5];
int yy[NMAX + 5];
bool side[NMAX + 5];
vector<int> graph[NMAX + 5];
bool viz[NMAX + 5];
int l[NMAX + 5];
int r[NMAX + 5];

bool pairup(int nod) {
    if(viz[nod]) return false;
    viz[nod] = true;
    for(auto it:graph[nod]) {
        if(r[it] == 0) {
            l[nod] = it;
            r[it] = nod;
            return true;
        }
    }
    for(auto it:graph[nod]) {
        if(pairup(r[it])) {
            l[nod] = it;
            r[it] = nod;
            return true;
        }
    }

    return false;
}

int cuplaj() {
    bool ok = true;

    int c = 0;
    while(ok) {
        memset(viz,0,sizeof(viz));
        ok = false;

        for(int i = 1; i <= n; i++) {
            if(side[i] == true && l[i] == 0 && pairup(i)) {
                ok = true;
                c++;
            }
        }
    }

    return c;
}

int main() {

    fscanf(f,"%d",&n);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d %d %d %d",&x[i],&y[i],&xx[i],&yy[i]);
        side[i] = (x[i] == xx[i]);
        if(x[i] > xx[i]) {
            swap(x[i],xx[i]);
        }
        if(y[i] > yy[i]) {
            swap(y[i],yy[i]);
        }
        for(int j = 1; j < i; j++) {
            if(side[i] != side[j]) {
                int px = (side[i] == true ? x[i] : x[j]);
                int py = (side[i] == false ? y[i] : y[j]);
                if(side[i] == true && y[i] <= py && py <= yy[i] && x[j] <= px && px <= xx[j]) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
                else if(side[i] == false && y[j] <= py && py <= yy[j] && x[i] <= px && px <= xx[i]) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
    }

    fprintf(g,"%d\n",n - cuplaj());

    fclose(f);
    fclose(g);

    return 0;
}
