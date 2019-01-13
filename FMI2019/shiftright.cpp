//#define JUDGE
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("shiftright.in","r");
FILE *g = fopen("shiftright.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int NMAX = 1e5;
const int SIGMA = 30;

int n;
char a[NMAX + 5];
char b[NMAX + 5];

vector<pair<int,int> > graph[SIGMA + 5];
int fr[SIGMA + 5];
bool taken[NMAX + 5];

vector<int> ciclueuler(int nod) {
    vector<int> ans;
    while(graph[nod].size() && taken[graph[nod].back().second]) {
        graph[nod].pop_back();
    }

    if(graph[nod].size()) {
        pair<int,int> to = graph[nod].back();
        graph[nod].pop_back();
        taken[to.second] = true;
        ans = ciclueuler(to.first);
        ans.push_back(to.second);
    }
    return ans;
}

int main() {

    fgets(a + 1,NMAX + 2,f);
    fgets(b + 1,NMAX + 2,f);

    n = strlen(a + 1);
    n -= (a[n] == '\n');

    for(int i = 1; i <= n; i++) {
        if(a[i] != b[i]) {
            graph[a[i] - 'a' + 1].push_back({b[i] - 'a' + 1,i - 1});
        }
        fr[a[i] - 'a' + 1]++;
        fr[b[i] - 'a' + 1]--;
    }

    for(int i = 1; i <= SIGMA; i++) {
        if(fr[i] != 0) {
            fprintf(g,"-1\n");
            return 0;
        }
    }

    vector<vector<int>> ans;

    for(int i = 1; i <= SIGMA; i++) {
        vector<int> tmp = ciclueuler(i);
        if(!tmp.empty()) {
            ans.push_back(tmp);
        }
    }

    fprintf(g,"%d\n",ans.size());

    for(auto it:ans) {
        fprintf(g,"%d ",it.size());
        for(auto it2:it) {
            fprintf(g,"%d ",it2);
        }
        fprintf(g,"\n");
    }

    return 0;
}
