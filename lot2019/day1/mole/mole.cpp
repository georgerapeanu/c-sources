#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int ask(vector<int> guess) {
    printf("ask ");
    for(auto it:guess) {
        printf("%d ",it);
    }
    printf("\n");
    fflush(stdout);
    int ans;
    scanf("%d",&ans);
    return ans;
}

vector<int> find_standings(int n) {
    vector<int> v;

    for(int i = 1; i <= n; i++) {
        v.push_back(i);
    }

    int cycles = n - ask(v);

    for(int i = 1; i < n; i++) {
        swap(v[0],v[i]);
        int new_cycles = n - ask(v);
        if(new_cycles > cycles) {
            swap(v[0],v[i]);
        }
        else {
            cycles = new_cycles;
        }
    }

    vector<int> order;

    for(int i = 1; i <= n; i++) {
        order.push_back(i);
    }

    sort(order.begin() + 1,order.end(),[&](int a,int b) {
        swap(v[0],v[a - 1]);
        swap(v[0],v[b - 1]);

        int cycles = n - ask(v);

        swap(v[b - 1],v[0]);
        swap(v[a - 1],v[0]);

        return (cycles == 3);
    });
    vector<int> ans(n,0);

    for(int i = 0; i < (int)order.size(); i++) {
        ans[order[(i + 1) % n] - 1] = v[order[i] - 1];
    }

    return ans;
}

int main() {

    int n;
    scanf("%d",&n);

    vector<int> ans = find_standings(n);

    printf("return ");
    for(auto it:ans) {
        printf("%d ",it);
    }
    printf("\n");

    return 0;
}
