#include "secret.h"

using namespace std;

int stuff[11][1005];
int global_n;

void build(int stage,int st,int dr,int a[]) {

    if(st == dr) {
        stuff[stage][st] = a[st];
        return ;
    }

    int mid = (st + dr) / 2;

    stuff[stage][mid] = a[mid];
    stuff[stage][mid + 1] = a[mid + 1];

    for(int i = mid - 1; i >= st; i--) {
        stuff[stage][i] = Secret(a[i],stuff[stage][i + 1]);
    }

    for(int i = mid + 2; i <= dr; i++) {
        stuff[stage][i] = Secret(stuff[stage][i - 1],a[i]);
    }

    build(stage + 1,st,mid,a);
    build(stage + 1,mid + 1,dr,a);
}

int query(int stage,int st,int dr,int l,int r) {

    int mid = (st + dr) / 2;

    if(l <= mid && mid <= r) {
        if(r == mid) {
            return stuff[stage][l];
        }
        return Secret(stuff[stage][l],stuff[stage][r]);
    }
    else if(mid < l) {
        return query(stage + 1,mid + 1,dr,l,r);
    }
    else {
        return query(stage + 1,st,mid,l,r);
    }
}

void Init(int n, int a[]) {
    global_n = n;
    build(0,0,n - 1,a);
}

int Query(int l, int r) {
    return query(0,0,global_n - 1,l,r);
}
