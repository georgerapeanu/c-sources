#include "brperm.h"
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

string v;
void init(int n, const char s[]) {
    
    for(int i = 0;i < n;i++){
        v += s[i];
    }

    return;
}

int query(int i, int k) {
    
    if(i + (1 << k) - 1 >= (int)v.size()){
        return 0;
    }

    for(int pos = 0;pos < (1 << k);pos++){
        int rev_pos = 0;
        for(int i = 0;i < k;i++){
            rev_pos = rev_pos * 2 + ((pos >> i) & 1);
        }
        if(v[i + pos] != v[i + rev_pos]){
            return 0;
        }
    }

    return 1;
}
