#include <cstdio>
#include <vector>

using namespace std;

FILE *f = fopen("arbore.in","r");
FILE *f2 = fopen("arbore.out","r");
FILE *g = fopen("arbore.ok","w");
const int NMAX = 1e5;
const int MMAX = 1e5;

int n,m;
int val[NMAX + 5];
vector<int> graph[NMAX + 5];
int father[NMAX + 5];

void predfs(int nod,int tata) {
    father[nod] = tata;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        predfs(it,nod);
    }
}

void update(int nod,int delta) {
    val[nod] += delta;
    for(auto it:graph[nod]) {
        if(it == father[nod]) {
            continue;
        }
        update(it,delta);
    }
}

int main() {

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i < n; i++) {
        int u,v;
        fscanf(f,"%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    predfs(1,0);

    while(m--) {
        int t,s,p;

        fscanf(f,"%d",&t);

        if(t == 1) {
            fscanf(f,"%d %d",&p,&s);
            update(p,s);
        }
        else {
            fscanf(f,"%d",&s);
            int ans = -1;
            for(int i = 1; i <= n; i++) {
                if(val[i] == s) {
                    ans = i;
                }
            }
            fprintf(g,"%d\n",ans);
            fflush(g);
            int other_ans;
            fscanf(f2,"%d",&other_ans);
            if(other_ans != -1) {
                if(val[other_ans] != s) {
                    printf("WA sum doesn't match out\n");
                    while(true);
                }
            }
            else if(ans != -1) {
                printf("WA there is an answer but main didn't find it\n");
                while(true);
            }
        }
    }

    printf("OK\n");

    fclose(f);
    fclose(f2);

    return 0;
}
