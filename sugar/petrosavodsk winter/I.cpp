#include <iostream>
#include <algorithm>

using namespace std;

const int NMAX = 1e4;
const int KMAX = 10;

int n,k;
int height[NMAX + 5];
int top[NMAX + 5];
pair<int,int> stacks[NMAX + 5];

int main(){

    cin >> n >> k;

    for(int i = 1;i <= n;i++){
        cin >> top[i];
        height[i] = k;
    }

    while(1){
        int x = 0;

        long long best = 1LL << 60;
        long long total = 0;
        long long pref = 0;

        for(int i = 1;i <= n;i++){
            stacks[i] = {top[i],height[i]};
            if(height[i])total += (1 << (2 * height[i]));
        }

        sort(stacks + 1,stacks + 1 + n);

        for(int i = 1;i <= n;i++){
            if(stacks[i].second == 0){
                continue;
            }    
            pref += (1 << (2 * stacks[i].second));
            if(abs(total - 2 * pref) <= best){
                best = abs(total - 2 * pref);
                x = stacks[i].first;
            }
        }

        cout << x << endl;

        string op;
        cin >> op;
        if(op == "End"){
            exit(0);
        }

        if(op == "<="){
            for(int i = 1;i <= n;i++){
                height[i] -= (height[i] > 0) * (top[i] <= x);
                cin >> top[i];
            }
        }
        else{
            for(int i = 1;i <= n;i++){
                height[i] -= (height[i] > 0) * (top[i] >= x);
                cin >> top[i];
            }
        }
    }


    return 0;
}
