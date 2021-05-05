#include "fiboxor.h"
#include <cstdio>

static FILE *f = fopen("fiboxor.in","r");
static FILE *g = fopen("fiboxor.out","w");

static const int LEN = 1 << 12;
static char buff[LEN];
static int ind = LEN - 1;

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

long long i64() {
    long long ans = 0;

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

int main() {

    int q = i32();

    init(q);

    while(q--) {
        int k;
        long long l,r;
        k = i32();
        l = i64();
        r = i64();

        fprintf(g,"%d\n",query(k,l,r));
    }

    fclose(f);
    fclose(g);

    return 0;
}
