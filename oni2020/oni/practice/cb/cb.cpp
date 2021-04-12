#include "cb.h"

using namespace std;

void solve(int N){
    int l = 0,r = N;

    while(r - l > 1){
        int mid = (l + r) / 2;
        if(query(mid)){
            r = mid;
        }else{
            l = mid;
        }
    }

    answer(r);
}
