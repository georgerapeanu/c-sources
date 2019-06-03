#include <bits/stdc++.h>

using namespace std;

int n,x;

bool not_aval[1 << 18];

int main() {

    scanf("%d %d",&n,&x);

    not_aval[0] = true;
    not_aval[x] = true;

    int last = 0;

    vector<int> v;

    for(int i = 0; i < (1 << n); i++) {
        if(not_aval[i]) {
            continue;
        }
        not_aval[i] = true;
        not_aval[i ^ x] = true;
        v.push_back(i ^ last);
        last = i;
    }

    printf("%d\n",(int)v.size());
    for(auto it:v) {
        printf("%d ",it);
    }

    return 0;
}
