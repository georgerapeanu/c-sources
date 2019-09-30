#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

int n,k;
int a[55];
int tmp[55];
int cnt[55];

vector<pair<int,int> > op;

int dist(int a,int b) {
    if(b < a) {
        b += k;
    }
    return b - a;
}

void do_tetris() {
    int mi = a[1];

    for(int i = 1; i <= n; i++) {
        mi = min(mi,a[i]);
    }

    for(int i = 1; i <= n; i++) {
        a[i] -= mi;
    }
}

void get_same_height_range() {
    int ma = 0;

    for(int i = 1; i <= n; i++) {
        ma = max(ma,a[i]);
    }

    for(int i = 1; i <= n; i++) {
        while(ma - a[i] >= k) {
            a[i] += k;
            op.push_back({1,i});
        }
    }
}

void do_bar(int pos,int cnt) {
    for(int x = 1; x <= cnt; x++) {
        op.push_back({2,pos});
    }
    for(int i = 1; i <= n; i++) {
        if(pos <= i && i < pos + k) {
            a[i] += cnt;
        }
        else {
            a[i] += 2 * k;
            op.push_back({1,i});
            op.push_back({1,i});
        }
    }
}

int main() {

    scanf("%d %d",&n,&k);

    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
    }

    int real_h = -1;

    for(int h = 0; h < k; h++) {
        for(int i = 1; i <= n; i++) {
            tmp[i] = a[i] % k;
        }

        for(int i = 1; i <= n - k + 1; i++) {
            cnt[i] = dist(tmp[i],h);
            for(int j = i; j < i + k; j++) {
                tmp[j] += cnt[i];
                tmp[j] %= k;
            }
        }

        bool ok = true;

        for(int i = 1; i <= n; i++) {
            if(tmp[i] != h) {
                ok = false;
                break;
            }
        }
        if(ok == true) {
            real_h = h;
            break;
        }
    }

    if(real_h == -1) {
        printf("-1\n");
        return 0;
    }

    for(int i = 1; i <= n - k + 1; i++) {
        get_same_height_range();
        do_tetris();
        do_bar(i,cnt[i]);
        do_tetris();
    }

    get_same_height_range();
    do_tetris();

    assert((int)op.size() <= 1e4);

    printf("%d\n",op.size());

    for(auto it:op) {
        printf("%d %d\n",it.first,it.second);
    }

    return 0;
}
