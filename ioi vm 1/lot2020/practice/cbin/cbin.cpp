#include "cbin.h"
 
using namespace std;

void solve(int N){
    int st = 0,dr = N;

    while(dr - st > 1){
        int mid = (st + dr) / 2;
        if(query(mid)){
            dr = mid;
        }
        else{
            st = mid;
        }
    }

    answer(dr);
}
