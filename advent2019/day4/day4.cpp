#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

bool ok(int val) {
    bool has_same = false;
    bool incr = true;

    int c = -1;
    int uc = -1;
    int uuc = -1;

    vector<int> cf;

    while(val) {
        uuc = uc;
        uc = c;
        c = val % 10;
        val /= 10;

        if(uc != -1) {
            incr &= (uc >= c);
        }
        cf.push_back(c);
    }

    for(int i = 2; i <= (int)cf.size(); i++) {
        if(cf[i - 1] == cf[i - 2] && (i >= (int)cf.size() || cf[i] != cf[i - 1]) && (i <3 || cf[i - 3] != cf[i - 2])) {
            has_same = true;
        }
    }

    return has_same & incr;
}

int main() {

    int ans = 0;
    int l,r;

    scanf("%d-%d",&l,&r);

    l = max(l,(int)1e5);
    r = min(r + 1,(int)1e6) - 1;

    for(int i = l; i <= r; i++) {
        if(ok(i)) {
            ans++;
        }
    }

    printf("%d\n",ans);

    return 0;
}
