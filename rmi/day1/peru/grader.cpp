#include<iostream>
#include "peru.h"
using namespace std;

static int s[2500005];
static int n, k;
int main(){
    cin>> n >> k;
    for(int i = 0; i < n; i++){
        cin>> s[i];
    }
    int ans = solve(n, k, s);
    cout<< ans <<"\n";
    return 0;
}
