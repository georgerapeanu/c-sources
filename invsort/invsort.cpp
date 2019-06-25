#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("invsort.in","r");
FILE *g = fopen("invsort.out","w");

const int NMAX = 32000;

int n;
pair<int,int> v[NMAX + 5];
pair<int,int> nv[NMAX + 5];
int tmp[NMAX + 5];

void cst_srt(int st,int dr) {
    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    cst_srt(st,mid);
    cst_srt(mid + 1,dr);

    int i = st,j = dr;
    while(j > mid && tmp[j] == 1) {
        j--;
    }
    while(i <= mid && tmp[i] == 0) {
        i++;
    }

    if(i <= mid && j > mid) {
        reverse(v + i,v + 1 + j);
        reverse(tmp + i,tmp + 1 + j);
        fprintf(g,"%d %d\n",i,j);
    }
}

void solve(int st,int dr) {
    if(st == dr) {
        return ;
    }

    int mid = (st + dr) / 2;

    for(int i = st; i <= dr; i++) {
        tmp[i] = (v[i] > nv[mid]);
    }

    cst_srt(st,dr);

    mid = st;

    while(tmp[mid] == 0) {
        mid++;
    }
    mid--;

    solve(st,mid);
    solve(mid + 1,dr);
}

int main() {

    fscanf(f,"%d",&n);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i].first);
        v[i].second = i;
        nv[i] = v[i];
    }

    sort(nv + 1,nv + 1 + n);

    solve(1,n);

    fclose(f);
    fclose(g);

    return 0;
}
