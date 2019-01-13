#define JUDGE
#include <cstdio>
#include <algorithm>

using namespace std;

#ifdef JUDGE
FILE *f = fopen("calorifer.in","r");
FILE *g = fopen("calorifer.out","w");
#else
FILE *f = stdin;
FILE *g = stdout;
#endif

const int NMAX = 1e5;

int n;
pair<pair<int,int>,int> v[NMAX + 5];

bool cmp(pair<pair<int,int>,int> &a, pair<pair<int,int>,int> &b) {
    if(a.first.first != b.first.first) {
        return a.first.first > b.first.first;
    }

    if(a.first.second != b.first.second) {
        return a.first.second < b.first.second;
    }

    return a.second < b.second;
}

int main() {

    fscanf(f,"%d",&n);

    int bval = -1;

    for(int i = 1; i <= n; i++) {
        int val;
        fscanf(f,"%d",&val);
        v[i].second = val;

        while(val % 2 == 0) {
            v[i].first.first++;
            val /= 2;
        }

        while(val % 3 == 0) {
            v[i].first.second++;
            val /= 3;
        }

        if(bval == -1) {
            bval = val;
        }
        else if(bval != val) {
            fprintf(g,"-1\n");
            return 0;
        }
    }

    sort(v + 1,v + 1 + n,cmp);

    for(int i = 2; i <= n; i++) {
        if(!(v[i - 1].first.first >= v[i].first.first && v[i - 1].first.second <= v[i].first.second)) {
            fprintf(g,"-1\n");
            return 0;
        }
    }

    for(int i = 1; i <= n; i++) {
        fprintf(g,"%d ",v[i].second);
    }

    return 0;
}
