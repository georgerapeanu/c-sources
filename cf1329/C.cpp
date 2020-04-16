#include <bits/stdc++.h>

using namespace std;

int t;
int h,g;
int v[1 << 22];
int pref_node[1 << 22];

void solve(int nod,vector<int> &op,long long &sum) {
    while(pref_node[nod] >= (1 << g)) {
        op.push_back(nod);
        int root = nod;
        sum -= v[nod];
        while(v[root * 2] || v[root * 2 + 1]) {
            if(v[root * 2] > v[root * 2 + 1]) {
                v[root] = v[root * 2];
                root = root * 2;
            }
            else {
                v[root] = v[root * 2 + 1];
                root = root * 2 + 1;
            }
        }
        v[root] = 0;
        root /= 2;
        while(root) {
            if(v[root * 2] == 0 && v[root * 2 + 1] == 0) {
                pref_node[root] = root;
            }
            else if(v[root * 2] > v[root * 2 + 1]) {
                pref_node[root] = pref_node[root * 2];
            }
            else {
                pref_node[root] = pref_node[root * 2 + 1];
            }
            root /= 2;
        }
    }
    if(v[nod * 2]) {
        solve(nod * 2,op,sum);
    }
    if(v[nod * 2 + 1]) {
        solve(nod * 2 + 1,op,sum);
    }
}

int main() {

    scanf("%d",&t);

    while(t--) {

        scanf("%d %d",&h,&g);

        long long sum = 0;
        for(int i = 1; i < (1 << h); i++) {
            scanf("%d",&v[i]);
            sum += v[i];
        }

        for(int i = (1 << h) - 1; i; i--) {
            if(v[2 * i] || v[2 * i + 1]) {
                if(v[2 * i] > v[2 * i + 1]) {
                    pref_node[i] = pref_node[2 * i];
                }
                else {
                    pref_node[i] = pref_node[2 * i + 1];
                }
            }
            else {
                pref_node[i] = i;
            }
        }
        vector<int> op;
        solve(1,op,sum);

        printf("%lld\n",sum);
        for(auto it:op) {
            printf("%d ",it);
        }
        printf("\n");

        for(int i = 1; i < (1 << h); i++) {
            v[i] = pref_node[i] = 0;
        }
    }

    return 0;
}
