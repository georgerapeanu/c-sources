#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

FILE *f = fopen("bfs2.in","r");
FILE *g = fopen("bfs2.out","w");

const int NMAX = 1e5;

int n,m,k;
int a[NMAX + 5];
int b[NMAX + 5];

long long pref_a[NMAX + 5];
long long pref_b[NMAX + 5];

int find_lin(long long sum,int i,bool inclusive) { ///last > sum
    sum -= pref_a[i];
    int l = -1,r = m + 1;

    while(r - l > 1) {
        int mid = (l + r) / 2;

        if(pref_b[mid] + inclusive > sum) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return l;
}

int find_col(long long sum,int i,bool inclusive) { ///last < sum
    sum -= pref_b[i];
    int l = -1,r = n + 1;

    while(r - l > 1) {
        int mid = (l + r) / 2;

        if(pref_a[mid] < sum + inclusive) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return l;
}

pair<int,int> get_lin_segm(int i) {
    pair<int,int> ans;
    ans.first = find_lin(k,i,false) + 1;
    ans.second = find_lin(-k,i,true);
    return ans;
}

pair<int,int> get_col_segm(int i) {
    pair<int,int> ans;
    ans.first = find_col(-k,i,false) + 1;
    ans.second = find_col(k,i,true);
    return ans;
}

set<int> bad;

void swap_lines(int u,int v) {
    swap(a[u],a[v]);
    pref_a[u] = pref_a[u - 1] + a[u];
    pref_a[v] = pref_a[v - 1] + a[v];
}

void swap_cols(int u,int v) {
    swap(b[u],b[v]);
    pref_b[u] = pref_b[u - 1] + b[u];
    pref_b[v] = pref_b[v - 1] + b[v];
}

bool is_bad(int i) {
    pair<int,int> a = get_lin_segm(i);
    pair<int,int> b = get_lin_segm(i + 1);

    if(a.first > a.second || b.first > b.second) {
        return true;
    }

    return (a.second < b.first || b.second < a.first);

}

void recalc(int i) {
    if(!(0 <= i && i < n)) {
        return ;
    }
    if(is_bad(i)) {
        bad.insert(i);
    }
    else {
        bad.erase(i);
    }
}

int main() {

    fscanf(f,"%d %d %d",&n,&m,&k);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&a[i]);
        pref_a[i] = a[i] + pref_a[i - 1];
    }

    for(int i = 1; i <= m; i++) {
        fscanf(f,"%d",&b[i]);
        b[i] *= -1;
        pref_b[i] = b[i] + pref_b[i - 1];
    }

    for(int i = 0; i < n; i++) {
        recalc(i);
    }

    int q;

    fscanf(f,"%d\n",&q);

    while(q--) {
        char c;
        int u,v;
        fscanf(f,"%c %d %d\n",&c,&u,&v);

        if(u > v) {
            swap(u,v);
        }

        if(c == 'B') {
            swap_lines(u,v);
            recalc(u - 1);
            recalc(u);
        }
        else {
            pair<int,int> a = get_col_segm(u);
            swap_cols(u,v);
            pair<int,int> b = get_col_segm(u);
            recalc(a.first - 1);
            recalc(a.first);
            recalc(b.first - 1);
            recalc(b.first);
            recalc(a.second - 1);
            recalc(a.second);
            recalc(b.second - 1);
            recalc(b.second);
        }

        fprintf(g,"%d\n",int(bad.empty()));
    }



    fclose(f);
    fclose(g);

    return 0;
}

