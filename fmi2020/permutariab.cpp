#include <cstdio>

using namespace std;

FILE *f = fopen("permutariab.in","r");
FILE *g = fopen("permutariab.out","w");

const int NMAX = 1e5;

int n;
int inva[NMAX + 5];
int b[NMAX + 5];

const int LEN = 1 << 14;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int tmp[NMAX + 5];

long long solve(int st,int dr) {
    if(st == dr) {
        return 0;
    }
    int mid = (st + dr) / 2;
    long long ans = solve(st,mid) + solve(mid + 1,dr);
    int i = st;
    int j = mid + 1;

    int lst = st - 1;

    while(i <= mid && j <= dr) {
        if(b[i] < b[j]) {
            tmp[++lst] = b[i];
            ans += (j - mid - 1);
            i++;
        }
        else {
            tmp[++lst] = b[j];
            j++;
        }
    }

    while(i <= mid) {
        tmp[++lst] = b[i];
        ans += (j - mid - 1);
        i++;
    }
    while(j <= dr) {
        tmp[++lst] = b[j];
        j++;
    }

    for(int i = st; i <= dr; i++) {
        b[i] = tmp[i];
    }

    return ans;
}

int main() {

    n = i32();

    for(int i = 1; i <= n; i++) {
        int val;
        val = i32();;
        inva[val] = i;
    }

    for(int i = 1; i <= n; i++) {
        int val;
        val = i32();
        b[i] = inva[val];
    }

    fprintf(g,"%lld\n",solve(1,n));

    fclose(f);
    fclose(g);
    return 0;
}

